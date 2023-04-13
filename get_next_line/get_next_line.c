#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	char *buffer = malloc(10000);
	char chr;
	int i = 0;
	int readed_byte = 0;

	readed_byte = read(fd, &chr, 1);
	// hata olursa -1, dosya içeriği boş ise 0 döner.
	if (readed_byte < 1)
	{
		free(buffer);
		return NULL;
	}
	while (readed_byte > 0)
	{
		buffer[i] = chr;
		// satır sonuna geldik, daha okuma.
		if (chr == '\n')
			break;
		i++;
		readed_byte = read(fd, &chr, 1);
	}
	// eğer okumaya devam ederken hata olduysa
	if (readed_byte == -1)
	{
		free(buffer);
		return NULL;
	}
	// son okuduğu karakter \n ise alt satırda var demektir.
	// son satır hariç tüm \n yazdırılmalı.
	// son satırda \n olmayacağı için bir şey yapmayacak zaten.
	if (buffer[i] == '\n')
		i++;
	buffer[i] = '\0';
	return buffer;
}

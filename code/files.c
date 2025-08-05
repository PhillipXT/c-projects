#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Commands:
//		xxd database.db		> Show the binary data of the file
//		wc -c database.db	> Show the metadata of the file
//		stat database.db	> Show file statistics
//		man stat			> Manpage for the linux command 'stat'
//		man 2 stat			> Manpage for the c keyword 'stat'
// Create the db file manually:
//		echo -ne "\x01\x00\x41\x00\x08\x00\x00\x00" > newdb.db

struct database_header_t {
	unsigned short version;
	unsigned short employees;
	unsigned int filesize;
};

int write_file(char *filename) {

	struct database_header_t head = {0};

	head.version = 1;
	head.employees = 65;
	head.filesize = sizeof(head);

	int fd = open(filename, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	write(fd, &head, sizeof(head));

	close(fd);

}

int read_file(char *filename) {

	struct database_header_t head = {0};
	struct stat dbStat = {0};

	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	int bytes = read(fd, &head, sizeof(head));
	if (bytes != sizeof(head)) {
		perror("read");
		close(fd);
		return -1;
	}

	printf("DB Version: %u\n", head.version);
	printf("DB Employees: %u\n", head.employees);
	printf("DB File Length: %u\n", head.filesize);

	if (fstat(fd, &dbStat) < 0) {
		perror("stat");
		close(fd);
		return -1;
	}

	printf("DB file length, reported by stat: %lu\n", dbStat.st_size);

	if (dbStat.st_size != head.filesize) {
		printf("GET OUT OF HERE HACKER!\n");
		close(fd);
		return -2;
	}

	return 0;
}

int main(int argc, char **argv) {
	struct database_header_t header = {0};

	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 0;
	}

	int fd = write_file(argv[1]);
	if (fd == -1) {
		return -1;
	}

	fd = read_file(argv[1]);
	if (fd == -1) {
		return -1;
	}

	return 0;
}
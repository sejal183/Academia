#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    int fd = open("./database/accounts/admin", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct flock fl;
    fl.l_type = F_UNLCK;  // Release locks
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;  // Unlock the entire file

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Rest of your code here

    close(fd);
    return 0;
}

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto
INCLUDE_PATHS = -I/opt/homebrew/include

SRCS = main.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

main: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -MMD -MP -c $< -o $@

clean:
	rm -f main $(OBJS) $(DEPS)

-include $(DEPS)

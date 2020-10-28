#define NEUROME_LOG_INTERNAL
#include <log/log.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int log_level = LOG_LEVEL;
_Bool log_colored;

static const struct {
	const char *name;
	const char *color;
} levels[] = {
	[LOG_TRACE] = {.name = "TRACE", .color = "\x1b[94m"},
	[LOG_DEBUG] = {.name = "DEBUG", .color = "\x1b[36m"},
	[LOG_INFO] = {.name = "INFO", .color = "\x1b[32m"},
	[LOG_WARN] = {.name = "WARN", .color = "\x1b[33m"},
	[LOG_ERROR] = {.name = "ERROR", .color = "\x1b[31m"},
	[LOG_FATAL] = {.name = "FATAL", .color = "\x1b[35m"}
};


void _log_log(int level, const char *file, unsigned line, const char *fmt, ...)
{
	va_list args;
	char time_buffer[32];
	time_t t = time(NULL);
	struct tm *loc_t = localtime(&t);

	strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", loc_t);
	time_buffer[sizeof(time_buffer) - 1] = '\0';
	if(log_colored)
		fprintf(
			stderr,
			"%s %s%-5s\x1b[0m \x1b[90m%s:%u:\x1b[0m ",
			time_buffer,
			levels[level].color,
			levels[level].name,
			file,
			line
		);
	else
		fprintf(
			stderr,
			"%s %-5s %s:%u: ",
			time_buffer,
			levels[level].name,
			file,
			line
		);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
	fflush(stderr);
}

void log_logo_print()
{
	if(log_colored){
		fprintf(stderr, "\x1b[94m    \x1b[90m         \x1b[94m _ \x1b[90m               \n");
		fprintf(stderr, "\x1b[94m|\\ |\x1b[90m  _      \x1b[94m|_)\x1b[90m  _  ._ _   _  \n");
		fprintf(stderr, "\x1b[94m| \\|\x1b[90m (/_ |_| \x1b[94m| \\\x1b[90m (_) | | | (/_ \n");
		fprintf(stderr, "\x1b[0m\n");
	} else {
		fprintf(stderr, "              _                 \n");
		fprintf(stderr, "|\\ |  _      |_)  _  ._ _   _  \n");
		fprintf(stderr, "| \\| (/_ |_| | \\ (_) | | | (/_ \n");
		fprintf(stderr, "\n");
	}
}

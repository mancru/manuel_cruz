#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <stdio.h>
#include <stdbool.h>

enum cfg_init_mode {
	CFG_NOT_DEF = -1,
	CFG_DEFAULT,
	CFG_GLIDER,
	CFG_RANDOM,
	_CFG_MAX_
};
#define CFG_N_INIT_MODES (_CFG_MAX_ - 1)

enum cfb_borders_mode {
	CFB_NOT_DEF = -1,
	CFB_DEFAULT,
	CFB_LIMITED,
	CFB_TOROIDAL,
	_CFB_MAX_
};
#define CFB_N_BORDERS_MODES (_CFB_MAX_ - 1)

struct config {
	bool show_help;
	int size_x;
	int size_y;
	enum cfg_init_mode init_mode;
	enum cfb_borders_mode borders_mode;
	char * cfg_file;
};

int config_parse_argv(struct config *config, int argc, char *argv[]);
void config_print(const struct config *config);
void config_print_usage(const char *arg0);

#endif

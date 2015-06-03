#include "irc.h"
#include <parmach.h>
#include <stdio.h>

#define IRC_CMD_GRP 1

#define PM_STR(x,n)\
const char x##_DATA[(n)] = #x;\
struct pm_str x##_STR = {\
	.data = x##_DATA,\
	.len = (n),\
};

#define PM_STRING(str)\
{\
	.self.ptr = (str),\
	.fn = pm_string_fn,\
}

PM_STR(PASS,4)
struct pm_parser pass_cmd = PM_STRING(&PASS_STR);

static
bool pass_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	if (!pm_parse_step(&pass_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	struct pm_result tmp;
	struct pm_str str;
	tmp.value.data.str = &str;
	if (!pm_parse_step(&pm_trail, src, len, state, &tmp)) {
		res->error.state = *state;
		return false;
	}
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_PASS;
	msg->pass.password = (struct irc_str) {
		.data = (char*)str.data,
		.len = str.len,
	};
	return true;
}

struct pm_parser pass = {
	.self.ptr = NULL,
	.fn = pass_fn,
};

PM_STR(NICK,4)
struct pm_parser nick_cmd = PM_STRING(&NICK_STR);

static
bool nick_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	if (!pm_parse_step(&nick_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	struct pm_result tmp;
	struct pm_str str;
	tmp.value.data.str = &str;
	if (!pm_parse_step(&pm_trail, src, len, state, &tmp)) {
		res->error.state = *state;
		return false;
	}
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_NICK;
	msg->nick.nickname = (struct irc_str) {
		.data = (char*)str.data,
		.len = str.len,
	};
	return true;
}

struct pm_parser nick = {
	.self.ptr = NULL,
	.fn = nick_fn,
};


bool irc_parse(const char *line, long len, struct irc_msg *msg)
{
	struct pm_parser msgs[IRC_CMD_SIZE] = {
		[IRC_PASS] = pass,
		[IRC_NICK] = nick,
	};

	struct pm_parsers parsers = {
		.data = msgs,
		.len = 2, // IRC_CMD_SIZE,
	};

	struct pm_parser choice;
	pm_choice_try(&parsers, &choice);

	struct pm_result res;
	res.value.data.ptr = msg;
	return pm_parse(&choice, line, len, &res);
}

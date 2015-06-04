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

struct irc_str to_irc_str(struct pm_str *str)
{
	return (struct irc_str) {
		.data = (char*)str->data,
		.len = str->len,
	};
}

struct pm_parser colon = {
	.self.prim.c = ':',
	.fn = pm_char_fn,
};

PM_STR(PASS,4)
struct pm_parser pass_cmd = PM_STRING(&PASS_STR);

static
bool pass_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_result r;
	struct pm_str password;
	// PASS <password>
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	// PASS
	if (!pm_parse_step(&pass_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <password>
	r.value.data.str = &password;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// Store result(s)
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_PASS;
	msg->pass.password = to_irc_str(&password);
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
	struct pm_result r;
	struct pm_str nickname;
	// NICK <nickname>
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	// NICK
	if (!pm_parse_step(&nick_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <nickname>
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// Store result(s)
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_NICK;
	msg->nick.nickname = to_irc_str(&nickname);
	return true;
}

struct pm_parser nick = {
	.self.ptr = NULL,
	.fn = nick_fn,
};

PM_STR(USER,4)
struct pm_parser user_cmd = PM_STRING(&USER_STR);

static
bool user_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_result r;
	struct pm_str user, mode, realname;
	// USER <user> <mode> * <realname>
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	// USER
	if (!pm_parse_step(&user_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	//  <user>' '
	r.value.data.str = &user;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// <mode>' '
	r.value.data.str = &mode;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// "* :"
	char *mode_delim_data = "* :";
	struct pm_str mode_delim_str = {
		.data = mode_delim_data,
		.len = 3,
	};
	struct pm_parser mode_delim;
	pm_string(&mode_delim_str, &mode_delim);
	if (!pm_parse_step(&mode_delim, src, len, state, NULL)) {
		return false;
	}
	// <realname>
	r.value.data.str = &realname;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// Store result(s)
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_USER;
	msg->user = (struct irc_user) {
		.user = to_irc_str(&user),
		.mode = to_irc_str(&mode),
		.realname = to_irc_str(&realname),
	};
	return true;
}

struct pm_parser user = {
	.self.ptr = NULL,
	.fn = user_fn,
};

PM_STR(OPER,4)
struct pm_parser oper_cmd = PM_STRING(&OPER_STR);

static
bool oper_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_result r;
	struct pm_str name, password;
	// OPER <name> <password>
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	// OPER
	if (!pm_parse_step(&oper_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <name>' '
	r.value.data.str = &name;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// <realname>
	r.value.data.str = &password;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// Store result(s)
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_OPER;
	msg->oper = (struct irc_oper) {
		.name = to_irc_str(&name),
		.password = to_irc_str(&password),
	};
	return true;
}

struct pm_parser oper = {
	.self.ptr = NULL,
	.fn = oper_fn,
};

PM_STR(MODE,4)
struct pm_parser mode_cmd = PM_STRING(&MODE_STR);

static
bool mode_user_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_result r;
	struct pm_str nickname, modes;
	// MODE <nickname> <modes>
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	// MODE
	if (!pm_parse_step(&mode_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <nickname>' '
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// <modes>
	r.value.data.str = &modes;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// Store result(s)
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_MODE_USER;
	msg->mode_user = (struct irc_mode_user) {
		.nickname = to_irc_str(&nickname),
		.modes = to_irc_str(&modes),
	};
	return true;
}

struct pm_parser mode_user = {
	.self.ptr = NULL,
	.fn = mode_user_fn,
};

PM_STR(SERVICE,7)
struct pm_parser service_cmd = PM_STRING(&SERVICE_STR);

static
bool service_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_result r;
	struct pm_str nickname, distribution, type, info;
	// SERVICE <nickname> <reserved> <distribution> <type> <reserved> <info>
	if (pm_out_of_range(src, len, state, res)) {
		return false;
	}
	// SERVICE
	if (!pm_parse_step(&service_cmd, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <nickname>' '
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <distribution>' '
	r.value.data.str = &distribution;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// <type>' '
	r.value.data.str = &type;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL)) {
		res->error.state = *state;
		return false;
	}
	// <info>
	r.value.data.str = &info;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		res->error.state = *state;
		return false;
	}
	// Store result(s)
	struct irc_msg *msg = res->value.data.ptr;
	msg->cmd = IRC_SERVICE;
	msg->service = (struct irc_service) {
		.nickname = to_irc_str(&nickname),
		.distribution = to_irc_str(&distribution),
		.type = to_irc_str(&type),
		.info = to_irc_str(&info),
	};
	return true;
}

struct pm_parser service = {
	.self.ptr = NULL,
	.fn = service_fn,
};

bool irc_parse(const char *line, long len, struct irc_msg *msg)
{
	struct pm_parser msgs[IRC_CMD_SIZE] = {
		[IRC_PASS] = pass,
		[IRC_NICK] = nick,
		[IRC_USER] = user,
		[IRC_OPER] = oper,
		[IRC_MODE_USER] = mode_user,
		[IRC_SERVICE] = service,
	};

	struct pm_parsers parsers = {
		.data = msgs,
		.len = 6, // IRC_CMD_SIZE,
	};

	struct pm_parser choice;
	pm_choice_try(&parsers, &choice);

	struct pm_result res;
	res.value.data.ptr = msg;
	return pm_parse(&choice, line, len, &res);
}

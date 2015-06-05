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

struct irc_opt_str to_irc_opt_str(struct pm_str *str, bool exist)
{
	struct irc_opt_str opt_str;
	opt_str.exist = exist;
	if (exist) {
		opt_str.str = (struct irc_str) {
			.data = (char*)str->data,
			.len = str->len,
		};
	}
	return opt_str;
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
	// PASS <password>
	struct pm_result r;
	struct pm_str password;
	struct irc_msg *msg = res->value.data.ptr;
	// PASS
	if (!pm_parse_step(&pass_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <password>
	r.value.data.str = &password;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_PASS;
	msg->pass.password = to_irc_str(&password);
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
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
	// NICK <nickname>
	struct pm_result r;
	struct pm_str nickname;
	struct irc_msg *msg = res->value.data.ptr;
	// NICK
	if (!pm_parse_step(&nick_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <nickname>
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_NICK;
	msg->nick.nickname = to_irc_str(&nickname);
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
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
	// USER <user> <mode> * :<realname>
	struct pm_result r;
	struct pm_str user, mode, realname;
	struct irc_msg *msg = res->value.data.ptr;
	// USER
	if (!pm_parse_step(&user_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	//  <user>' '
	r.value.data.str = &user;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <mode>' '
	r.value.data.str = &mode;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
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
		goto fail;
	}
	// <realname>
	r.value.data.str = &realname;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_USER;
	msg->user = (struct irc_user) {
		.user = to_irc_str(&user),
		.mode = to_irc_str(&mode),
		.realname = to_irc_str(&realname),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
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
	// OPER <name> <password>
	struct pm_result r;
	struct pm_str name, password;
	struct irc_msg *msg = res->value.data.ptr;
	// OPER
	if (!pm_parse_step(&oper_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <name>' '
	r.value.data.str = &name;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <realname>
	r.value.data.str = &password;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_OPER;
	msg->oper = (struct irc_oper) {
		.name = to_irc_str(&name),
		.password = to_irc_str(&password),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
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
	// MODE <nickname> <modes>
	struct pm_result r;
	struct pm_str nickname, modes;
	struct irc_msg *msg = res->value.data.ptr;
	// MODE
	if (!pm_parse_step(&mode_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <nickname>' '
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <modes>
	r.value.data.str = &modes;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_MODE_USER;
	msg->mode_user = (struct irc_mode_user) {
		.nickname = to_irc_str(&nickname),
		.modes = to_irc_str(&modes),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
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
	// SERVICE <nickname> <reserved> <distribution> <type> <reserved> :<info>
	struct pm_result r;
	struct pm_str nickname, distribution, type, info;
	struct irc_msg *msg = res->value.data.ptr;
	// SERVICE
	if (!pm_parse_step(&service_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <nickname>' '
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, len, state, NULL)) {
		goto fail;
	}
	// <distribution>' '
	r.value.data.str = &distribution;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <type>' '
	r.value.data.str = &type;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, len, state, NULL)) {
		goto fail;
	}
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL)) {
		goto fail;
	}
	// <info>
	r.value.data.str = &info;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_SERVICE;
	msg->service = (struct irc_service) {
		.nickname = to_irc_str(&nickname),
		.distribution = to_irc_str(&distribution),
		.type = to_irc_str(&type),
		.info = to_irc_str(&info),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

struct pm_parser service = {
	.self.ptr = NULL,
	.fn = service_fn,
};

PM_STR(QUIT,4)
struct pm_parser quit_cmd = PM_STRING(&QUIT_STR);

static
bool quit_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// QUIT[ :<msg>]
	struct pm_result r;
	struct pm_str quit_msg;
	struct irc_msg *msg = res->value.data.ptr;
	// QUIT
	if (!pm_parse_step(&quit_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto no_msg;
	}
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL)) {
		goto no_msg;
	}
	// <msg>
	r.value.data.str = &quit_msg;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto no_msg;
	}
	// Store result(s)
	msg->cmd = IRC_QUIT;
	msg->quit = (struct irc_quit) {
		.msg = (struct irc_opt_str) {
			.exist = true,
			.str = (struct irc_str) {
				.data = (char*)quit_msg.data,
				.len = quit_msg.len,
			}
		},
	};
	return true;
no_msg:
	msg->cmd = IRC_QUIT;
	msg->quit = (struct irc_quit) {
		.msg = (struct irc_opt_str) { .exist = false },
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

struct pm_parser quit = {
	.self.ptr = NULL,
	.fn = quit_fn,
};

PM_STR(SQUIT,5)
struct pm_parser squit_cmd = PM_STRING(&SQUIT_STR);

static
bool squit_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// SQUIT <server> :<comment>
	struct pm_result r;
	struct pm_str server, comment;
	struct irc_msg *msg = res->value.data.ptr;
	// SQUIT
	if (!pm_parse_step(&service_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <server>' '
	r.value.data.str = &server;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL)) {
		goto fail;
	}
	// <comment>
	r.value.data.str = &comment;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_SQUIT;
	msg->squit = (struct irc_squit) {
		.server = to_irc_str(&server),
		.comment = to_irc_str(&comment),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

struct pm_parser squit = {
	.self.ptr = NULL,
	.fn = squit_fn,
};

PM_STR(JOIN,5)
struct pm_parser join_cmd = PM_STRING(&JOIN_STR);

static
bool join_with_key_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// JOIN <channel>[ <key>]
	struct pm_result r;
	struct pm_str channel, key;
	struct irc_msg *msg = res->value.data.ptr;
	// JOIN
	if (!pm_parse_step(&join_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <channel>[' ']
	r.value.data.str = &channel;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r)) {
		goto fail;
	}
	// <key>
	r.value.data.str = &key;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_JOIN;
	msg->join = (struct irc_join) {
		.channel = to_irc_str(&channel),
		.key = to_irc_opt_str(&key, true),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

struct pm_parser join_with_key = {
	.self.ptr = NULL,
	.fn = join_with_key_fn,
};

static
bool join_no_key_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// JOIN <channel>[ <key>]
	struct pm_result r;
	struct pm_str channel;
	struct irc_msg *msg = res->value.data.ptr;
	// JOIN
	if (!pm_parse_step(&join_cmd, src, len, state, NULL)) {
		goto fail;
	}
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL)) {
		goto fail;
	}
	// <channel>
	r.value.data.str = &channel;
	if (!pm_parse_step(&pm_trail, src, len, state, &r)) {
		goto fail;
	}
	// Store result(s)
	msg->cmd = IRC_JOIN;
	msg->join = (struct irc_join) {
		.channel = to_irc_str(&channel),
		.key = to_irc_opt_str(NULL, false),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

struct pm_parser join_no_key = {
	.self.ptr = NULL,
	.fn = join_no_key_fn,
};

static
bool join_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_parser parser;
	struct pm_parser join_opts[2] = {
		[0] = join_with_key,
		[1] = join_no_key,
	};
	pm_or(join_opts, &parser);
	return pm_parse_step(&parser, src, len, state, res);
}

struct pm_parser join = {
	.self.ptr = NULL,
	.fn = join_fn,
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
		[IRC_QUIT] = quit,
		[IRC_SQUIT] = squit,
		//
		[IRC_JOIN] = join,
	};

	struct pm_parsers parsers = {
		.data = msgs,
		.len = 9, // IRC_CMD_SIZE,
	};

	struct pm_parser choice;
	pm_choice_try(&parsers, &choice);

	struct pm_result res;
	res.value.data.ptr = msg;
	return pm_parse(&choice, line, len, &res);
}

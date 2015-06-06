#include "irc.h"
#include <parmach.h>
#include <stdio.h>

#define IRC_CMD_GRP 1

const char PASS[] = "PASS";
const char NICK[] = "NICK";
const char USER[] = "USER";
const char OPER[] = "OPER";
const char MODE[] = "MODE";
const char SERVICE[] = "SERVICE";
const char QUIT[] = "QUIT";
const char SQUIT[] = "SQUIT";
const char JOIN[] = "JOIN";
const char PART[] = "PART";
const char TOPIC[] = "TOPIC";
const char NAMES[] = "NAMES";
const char LIST[] = "LIST";
const char INVITE[] = "INVITE";
const char KICK[] = "KICK";
const char PRIVMSG[] = "PRIVMSG";
const char NOTICE[] = "NOTICE";
const char MOTD[] = "MOTD";
const char LUSERS[] = "LUSERS";
const char VERSION[] = "VERSION";
const char STATS[] = "STATS";
const char LINKS[] = "LINKS";
const char TIME[] = "TIME";
const char CONNECT[] = "CONNECT";
const char TRACE[] = "TRACE";
const char ADMIN[] = "ADMIN";
const char INFO[] = "INFO";
const char SERVLIST[] = "SERVLIST";
const char SQUERY[] = "SQUERY";
const char WHO[] = "WHO";
const char WHOIS[] = "WHOIS";
const char WHOWAS[] = "WHOWAS";
const char KILL[] = "KILL";
const char PING[] = "PING";
const char PONG[] = "PONG";
const char ERROR[] = "ERROR";
const char AWAY[] = "AWAY";
const char REHASH[] = "REHASH";
const char DIE[] = "DIE";
const char RESTART[] = "RESTART";
const char SUMMON[] = "SUMMON";
const char USERS[] = "USERS";
const char WALLOPS[] = "WALLOPS";
const char USERHOST[] = "USERHOST";
const char ISON[] = "ISON";

struct pm_str pass_str = { PASS, 4 };
struct pm_str nick_str = { NICK, 4 };
struct pm_str user_str = { USER, 4 };
struct pm_str oper_str = { OPER, 4 };
struct pm_str mode_str = { MODE, 4 };
struct pm_str service_str = { SERVICE, 7 };
struct pm_str quit_str = { QUIT, 4 };
struct pm_str squit_str = { SQUIT, 5 };
struct pm_str join_str = { JOIN, 4 };
struct pm_str part_str = { PART, 4 };
struct pm_str topic_str = { TOPIC, 5 };
struct pm_str names_str = { NAMES, 6 };
struct pm_str list_str = { LIST, 4 };
struct pm_str invite_str = { INVITE, 6 };
struct pm_str kick_str = { KICK, 4 };
struct pm_str privmsg_str = { PRIVMSG, 7 };
struct pm_str notice_str = { NOTICE, 6 };
struct pm_str lusers_str = { LUSERS, 6 };
struct pm_str version_str = { VERSION, 7 };
struct pm_str stats_str = { STATS, 5 };
struct pm_str links_str = { LINKS, 5 };
struct pm_str time_str = { TIME, 4 };
struct pm_str connect_str = { CONNECT, 7 };
struct pm_str trace_str = { TRACE, 5 };
struct pm_str admin_str = { ADMIN, 5 };
struct pm_str info_str = { INFO, 4 };
struct pm_str servlist_str = { SERVLIST, 8 };
struct pm_str squery_str = { SQUERY, 6 };
struct pm_str who_str = { WHO, 3 };
struct pm_str whois_str = { WHOIS, 5 };
struct pm_str whowas_str = { WHOWAS, 6 };
struct pm_str kill_str = { KILL, 4 };
struct pm_str ping_str = { PING, 4 };
struct pm_str pong_str = { PONG, 4 };
struct pm_str error_str = { ERROR, 5 };
struct pm_str away_str = { AWAY, 4 };
struct pm_str rehash_str = { REHASH, 6 };
struct pm_str die_str = { DIE, 3 };
struct pm_str restart_str = { RESTART, 7 };
struct pm_str summon_str = { SUMMON, 6 };
struct pm_str users_str = { USERS, 5 };
struct pm_str wallops_str = { WALLOPS, 7 };
struct pm_str userhost_str = { USERHOST, 8 };
struct pm_str ison_str = { ISON, 4 };

struct pm_parser pass_cmd = { .self.ptr = &pass_str, pm_string_fn };
struct pm_parser nick_cmd = { .self.ptr = &nick_str, pm_string_fn };
struct pm_parser user_cmd = { .self.ptr = &user_str, pm_string_fn };
struct pm_parser oper_cmd = { .self.ptr = &oper_str, pm_string_fn };
struct pm_parser mode_cmd = { .self.ptr = &mode_str, pm_string_fn };
struct pm_parser service_cmd = { .self.ptr = &service_str, pm_string_fn };
struct pm_parser quit_cmd = { .self.ptr = &quit_str, pm_string_fn };
struct pm_parser join_cmd = { .self.ptr = &join_str, pm_string_fn };
struct pm_parser part_cmd = { .self.ptr = &part_str, pm_string_fn };
struct pm_parser topic_cmd = { .self.ptr = &topic_str, pm_string_fn };
struct pm_parser names_cmd = { .self.ptr = &names_str, pm_string_fn };
struct pm_parser list_cmd = { .self.ptr = &list_str, pm_string_fn };
struct pm_parser invite_cmd = { .self.ptr = &part_str, pm_string_fn };
struct pm_parser kick_cmd = { .self.ptr = &kick_str, pm_string_fn };
struct pm_parser privmsg_cmd = { .self.ptr = &privmsg_str, pm_string_fn };
struct pm_parser notice_cmd = { .self.ptr = &notice_str, pm_string_fn };
struct pm_parser lusers_cmd = { .self.ptr = &lusers_str, pm_string_fn };
struct pm_parser version_cmd = { .self.ptr = &version_str, pm_string_fn };
struct pm_parser stats_cmd = { .self.ptr = &stats_str, pm_string_fn };
struct pm_parser links_cmd = { .self.ptr = &links_str, pm_string_fn };
struct pm_parser time_cmd = { .self.ptr = &time_str, pm_string_fn };
struct pm_parser connect_cmd = { .self.ptr = &connect_str, pm_string_fn };
struct pm_parser trace_cmd = { .self.ptr = &trace_str, pm_string_fn };
struct pm_parser admin_cmd = { .self.ptr = &admin_str, pm_string_fn };
struct pm_parser info_cmd = { .self.ptr = &info_str, pm_string_fn };
struct pm_parser servlist_cmd = { .self.ptr = &servlist_str, pm_string_fn };
struct pm_parser squery_cmd = { .self.ptr = &squery_str, pm_string_fn };
struct pm_parser who_cmd = { .self.ptr = &who_str, pm_string_fn };
struct pm_parser whois_cmd = { .self.ptr = &whois_str, pm_string_fn };
struct pm_parser kill_cmd = { .self.ptr = &kill_str, pm_string_fn };
struct pm_parser ping_cmd = { .self.ptr = &ping_str, pm_string_fn };
struct pm_parser pong_cmd = { .self.ptr = &pong_str, pm_string_fn };
struct pm_parser error_cmd = { .self.ptr = &error_str, pm_string_fn };
struct pm_parser away_cmd = { .self.ptr = &away_str, pm_string_fn };
struct pm_parser rehash_cmd = { .self.ptr = &rehash_str, pm_string_fn };
struct pm_parser die_cmd = { .self.ptr = &die_str, pm_string_fn };
struct pm_parser restart_cmd = { .self.ptr = &restart_str, pm_string_fn };
struct pm_parser summon_cmd = { .self.ptr = &summon_str, pm_string_fn };
struct pm_parser users_cmd = { .self.ptr = &users_str, pm_string_fn };
struct pm_parser wallops_cmd = { .self.ptr = &wallops_str, pm_string_fn };
struct pm_parser userhost_cmd = { .self.ptr = &userhost_str, pm_string_fn };
struct pm_parser ison_cmd = { .self.ptr = &ison_str, pm_string_fn };

struct pm_parser colon = { .self.prim.c = ':', pm_char_fn };

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

static
bool pass_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// PASS <password>
	struct pm_result r;
	struct pm_str password;
	struct irc_msg *msg = res->value.data.ptr;
	// PASS
	if (!pm_parse_step(&pass_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <password>
	r.value.data.str = &password;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
	// Store result(s)
	msg->cmd = IRC_PASS;
	msg->pass.password = to_irc_str(&password);
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

static
bool nick_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// NICK <nickname>
	struct pm_result r;
	struct pm_str nickname;
	struct irc_msg *msg = res->value.data.ptr;
	// NICK
	if (!pm_parse_step(&nick_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <nickname>
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
	// Store result(s)
	msg->cmd = IRC_NICK;
	msg->nick.nickname = to_irc_str(&nickname);
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}


static
bool user_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// USER <user> <mode> * :<realname>
	struct pm_result r;
	struct pm_str user, mode, realname;
	struct irc_msg *msg = res->value.data.ptr;
	// USER
	if (!pm_parse_step(&user_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	//  <user>' '
	r.value.data.str = &user;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <mode>' '
	r.value.data.str = &mode;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// "* :"
	char *mode_delim_data = "* :";
	struct pm_str mode_delim_str = { .data = mode_delim_data, .len = 3 };
	struct pm_parser mode_delim;
	pm_string(&mode_delim_str, &mode_delim);
	if (!pm_parse_step(&mode_delim, src, len, state, NULL))
		goto fail;
	// <realname>
	r.value.data.str = &realname;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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


static
bool oper_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// OPER <name> <password>
	struct pm_result r;
	struct pm_str name, password;
	struct irc_msg *msg = res->value.data.ptr;
	// OPER
	if (!pm_parse_step(&oper_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <name>' '
	r.value.data.str = &name;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <realname>
	r.value.data.str = &password;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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

static
bool mode_user_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// MODE <nickname> <modes>
	struct pm_result r;
	struct pm_str nickname, modes;
	struct irc_msg *msg = res->value.data.ptr;
	// MODE
	if (!pm_parse_step(&mode_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <nickname>' '
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <modes>
	r.value.data.str = &modes;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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

static
bool service_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// SERVICE <nickname> <reserved> <distribution> <type> <reserved> :<info>
	struct pm_result r;
	struct pm_str nickname, distribution, type, info;
	struct irc_msg *msg = res->value.data.ptr;
	// SERVICE
	if (!pm_parse_step(&service_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <nickname>' '
	r.value.data.str = &nickname;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, len, state, NULL))
		goto fail;
	// <distribution>' '
	r.value.data.str = &distribution;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <type>' '
	r.value.data.str = &type;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, len, state, NULL))
		goto fail;
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL))
		goto fail;
	// <info>
	r.value.data.str = &info;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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

static
bool quit_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// QUIT[ :<msg>]
	struct pm_result r;
	struct pm_str quit_msg;
	struct irc_msg *msg = res->value.data.ptr;
	// QUIT
	if (!pm_parse_step(&quit_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto no_msg;
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL))
		goto no_msg;
	// <msg>
	r.value.data.str = &quit_msg;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto no_msg;
	// Store result(s)
	msg->cmd = IRC_QUIT;
	msg->quit = (struct irc_quit) {
		.msg = to_irc_opt_str(&quit_msg, true),
	};
	return true;
no_msg:
	msg->cmd = IRC_QUIT;
	msg->quit = (struct irc_quit) {
		.msg = to_irc_opt_str(NULL, false),
	};
	return true;
	// Store failure state
fail:
	res->error.state = *state;
	return false;
}

static
bool squit_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// SQUIT <server> :<comment>
	struct pm_result r;
	struct pm_str server, comment;
	struct irc_msg *msg = res->value.data.ptr;
	// SQUIT
	if (!pm_parse_step(&service_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <server>' '
	r.value.data.str = &server;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// ':'
	if (!pm_parse_step(&colon, src, len, state, NULL))
		goto fail;
	// <comment>
	r.value.data.str = &comment;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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

static
bool join_with_key_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// JOIN <channel>[ <key>]
	struct pm_result r;
	struct pm_str channel, key;
	struct irc_msg *msg = res->value.data.ptr;
	// JOIN
	if (!pm_parse_step(&join_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <channel>[' ']
	r.value.data.str = &channel;
	if (!pm_parse_step(&pm_until_space, src, len, state, &r))
		goto fail;
	// <key>
	r.value.data.str = &key;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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

static
bool join_no_key_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	// JOIN <channel>[ <key>]
	struct pm_result r;
	struct pm_str channel;
	struct irc_msg *msg = res->value.data.ptr;
	// JOIN
	if (!pm_parse_step(&join_cmd, src, len, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, len, state, NULL))
		goto fail;
	// <channel>
	r.value.data.str = &channel;
	if (!pm_parse_step(&pm_trail, src, len, state, &r))
		goto fail;
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

static
bool join_fn(const union pm_data d, const char *src, long len, struct pm_state *state, struct pm_result *res)
{
	struct pm_parser parser;
	struct pm_parser join_opts[2] = {
		{ .self.ptr = NULL, join_with_key_fn },
		{ .self.ptr = NULL, join_no_key_fn },
	};
	pm_or(join_opts, &parser);
	return pm_parse_step(&parser, src, len, state, res);
}

struct pm_parser user = { .self.ptr = NULL, user_fn };
struct pm_parser pass = { .self.ptr = NULL, pass_fn };
struct pm_parser nick = { .self.ptr = NULL, nick_fn };
struct pm_parser oper = { .self.ptr = NULL, oper_fn };
struct pm_parser mode_user = { .self.ptr = NULL, mode_user_fn };
struct pm_parser service = { .self.ptr = NULL, service_fn };
struct pm_parser quit = { .self.ptr = NULL, quit_fn };
struct pm_parser squit = { .self.ptr = NULL, squit_fn };
struct pm_parser join = { .self.ptr = NULL, join_fn };

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
		[IRC_JOIN] = join,
		[IRC_PART] = pm_fail,
		[IRC_MODE_CHANNEL] = pm_fail,
		[IRC_TOPIC] = pm_fail,
		[IRC_NAMES] = pm_fail,
		[IRC_LIST] = pm_fail,
		[IRC_INVITE] = pm_fail,
		[IRC_KICK] = pm_fail,
		[IRC_PRIVMSG] = pm_fail,
		[IRC_NOTICE] = pm_fail,
		[IRC_MOTD] = pm_fail,
		[IRC_LUSERS] = pm_fail,
		[IRC_VERSION] = pm_fail,
		[IRC_STATS] = pm_fail,
		[IRC_LINKS] = pm_fail,
		[IRC_TIME] = pm_fail,
		[IRC_CONNECT] = pm_fail,
		[IRC_TRACE] = pm_fail,
		[IRC_ADMIN] = pm_fail,
		[IRC_INFO] = pm_fail,
		[IRC_SERVLIST] = pm_fail,
		[IRC_SQUERY] = pm_fail,
		[IRC_WHO] = pm_fail,
		[IRC_WHOIS] = pm_fail,
		[IRC_WHOWAS] = pm_fail,
		[IRC_KILL] = pm_fail,
		[IRC_PING] = pm_fail,
		[IRC_PONG] = pm_fail,
		[IRC_ERROR] = pm_fail,
		[IRC_AWAY] = pm_fail,
		[IRC_DIE] = pm_fail,
		[IRC_RESTART] = pm_fail,
		[IRC_SUMMON] = pm_fail,
		[IRC_USERS] = pm_fail,
		[IRC_WALLOPS] = pm_fail,
		[IRC_USERHOST] = pm_fail,
		[IRC_ISON] = pm_fail,
		[IRC_NUMERIC] = pm_fail,
	};

	struct pm_parsers parsers = {
		.data = msgs,
		.len = IRC_CMD_SIZE,
	};

	struct pm_parser choice;
	pm_choice_try(&parsers, &choice);

	struct pm_result res;
	res.value.data.ptr = msg;
	return pm_parse(&choice, line, len, &res);
}

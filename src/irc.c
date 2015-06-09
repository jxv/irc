#include "irc.h"
#include <parmach.h>

char PASS[] = "PASS";
char NICK[] = "NICK";
char USER[] = "USER";
char OPER[] = "OPER";
char MODE[] = "MODE";
char SERVICE[] = "SERVICE";
char QUIT[] = "QUIT";
char SQUIT[] = "SQUIT";
char JOIN[] = "JOIN";
char PART[] = "PART";
char TOPIC[] = "TOPIC";
char NAMES[] = "NAMES";
char LIST[] = "LIST";
char INVITE[] = "INVITE";
char KICK[] = "KICK";
char PRIVMSG[] = "PRIVMSG";
char NOTICE[] = "NOTICE";
char MOTD[] = "MOTD";
char LUSERS[] = "LUSERS";
char VERSION[] = "VERSION";
char STATS[] = "STATS";
char LINKS[] = "LINKS";
char TIME[] = "TIME";
char CONNECT[] = "CONNECT";
char TRACE[] = "TRACE";
char ADMIN[] = "ADMIN";
char INFO[] = "INFO";
char SERVLIST[] = "SERVLIST";
char SQUERY[] = "SQUERY";
char WHO[] = "WHO";
char WHOIS[] = "WHOIS";
char WHOWAS[] = "WHOWAS";
char KILL[] = "KILL";
char PING[] = "PING";
char PONG[] = "PONG";
char ERROR[] = "ERROR";
char AWAY[] = "AWAY";
char REHASH[] = "REHASH";
char DIE[] = "DIE";
char RESTART[] = "RESTART";
char SUMMON[] = "SUMMON";
char USERS[] = "USERS";
char WALLOPS[] = "WALLOPS";
char USERHOST[] = "USERHOST";
char ISON[] = "ISON";

str_t pass_str = { PASS, 4 };
str_t nick_str = { NICK, 4 };
str_t user_str = { USER, 4 };
str_t oper_str = { OPER, 4 };
str_t mode_str = { MODE, 4 };
str_t service_str = { SERVICE, 7 };
str_t quit_str = { QUIT, 4 };
str_t squit_str = { SQUIT, 5 };
str_t join_str = { JOIN, 4 };
str_t part_str = { PART, 4 };
str_t topic_str = { TOPIC, 5 };
str_t names_str = { NAMES, 6 };
str_t list_str = { LIST, 4 };
str_t invite_str = { INVITE, 6 };
str_t kick_str = { KICK, 4 };
str_t privmsg_str = { PRIVMSG, 7 };
str_t notice_str = { NOTICE, 6 };
str_t lusers_str = { LUSERS, 6 };
str_t version_str = { VERSION, 7 };
str_t stats_str = { STATS, 5 };
str_t links_str = { LINKS, 5 };
str_t time_str = { TIME, 4 };
str_t connect_str = { CONNECT, 7 };
str_t trace_str = { TRACE, 5 };
str_t admin_str = { ADMIN, 5 };
str_t info_str = { INFO, 4 };
str_t servlist_str = { SERVLIST, 8 };
str_t squery_str = { SQUERY, 6 };
str_t who_str = { WHO, 3 };
str_t whois_str = { WHOIS, 5 };
str_t whowas_str = { WHOWAS, 6 };
str_t kill_str = { KILL, 4 };
str_t ping_str = { PING, 4 };
str_t pong_str = { PONG, 4 };
str_t error_str = { ERROR, 5 };
str_t away_str = { AWAY, 4 };
str_t rehash_str = { REHASH, 6 };
str_t die_str = { DIE, 3 };
str_t restart_str = { RESTART, 7 };
str_t summon_str = { SUMMON, 6 };
str_t users_str = { USERS, 5 };
str_t wallops_str = { WALLOPS, 7 };
str_t userhost_str = { USERHOST, 8 };
str_t ison_str = { ISON, 4 };

pm_parser_t pass_cmd = PM_STRING(&pass_str);
pm_parser_t nick_cmd = PM_STRING(&nick_str);
pm_parser_t user_cmd = PM_STRING(&user_str);
pm_parser_t oper_cmd = PM_STRING(&oper_str);
pm_parser_t mode_cmd = PM_STRING(&mode_str);
pm_parser_t service_cmd = PM_STRING(&service_str);
pm_parser_t quit_cmd = PM_STRING(&quit_str);
pm_parser_t join_cmd = PM_STRING(&join_str);
pm_parser_t part_cmd = PM_STRING(&part_str);
pm_parser_t topic_cmd = PM_STRING(&topic_str);
pm_parser_t names_cmd = PM_STRING(&names_str);
pm_parser_t list_cmd = PM_STRING(&list_str);
pm_parser_t invite_cmd = PM_STRING(&part_str);
pm_parser_t kick_cmd = PM_STRING(&kick_str);
pm_parser_t privmsg_cmd = PM_STRING(&privmsg_str);
pm_parser_t notice_cmd = PM_STRING(&notice_str);
pm_parser_t lusers_cmd = PM_STRING(&lusers_str);
pm_parser_t version_cmd = PM_STRING(&version_str);
pm_parser_t stats_cmd = PM_STRING(&stats_str);
pm_parser_t links_cmd = PM_STRING(&links_str);
pm_parser_t time_cmd = PM_STRING(&time_str);
pm_parser_t connect_cmd = PM_STRING(&connect_str);
pm_parser_t trace_cmd = PM_STRING(&trace_str);
pm_parser_t admin_cmd = PM_STRING(&admin_str);
pm_parser_t info_cmd = PM_STRING(&info_str);
pm_parser_t servlist_cmd = PM_STRING(&servlist_str);
pm_parser_t squery_cmd = PM_STRING(&squery_str);
pm_parser_t who_cmd = PM_STRING(&who_str);
pm_parser_t whois_cmd = PM_STRING(&whois_str);
pm_parser_t kill_cmd = PM_STRING(&kill_str);
pm_parser_t ping_cmd = PM_STRING(&ping_str);
pm_parser_t pong_cmd = PM_STRING(&pong_str);
pm_parser_t error_cmd = PM_STRING(&error_str);
pm_parser_t away_cmd = PM_STRING(&away_str);
pm_parser_t rehash_cmd = PM_STRING(&rehash_str);
pm_parser_t die_cmd = PM_STRING(&die_str);
pm_parser_t restart_cmd = PM_STRING(&restart_str);
pm_parser_t summon_cmd = PM_STRING(&summon_str);
pm_parser_t users_cmd = PM_STRING(&users_str);
pm_parser_t wallops_cmd = PM_STRING(&wallops_str);
pm_parser_t userhost_cmd = PM_STRING(&userhost_str);
pm_parser_t ison_cmd = PM_STRING(&ison_str);

pm_parser_t colon = PM_CHAR(':');

struct irc_str to_irc_str(str_t *str)
{
	return (struct irc_str) {
		.data = (char*)str->data,
		.len = str->len,
	};
}

struct irc_opt_str to_irc_opt_str(str_t *str, bool exist)
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
bool pass(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// PASS <password>
	pm_result_t r;
	str_t password;
	struct irc_msg *msg = res->data.ptr;
	// PASS
	if (!pm_parse_step(&pass_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <password>
	r.data.ptr = &password;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool nick(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// NICK <nickname>
	pm_result_t r;
	str_t nickname;
	struct irc_msg *msg = res->data.ptr;
	// NICK
	if (!pm_parse_step(&nick_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <nickname>
	r.data.ptr = &nickname;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool user(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// USER <user> <mode> * :<realname>
	pm_result_t r;
	str_t user, mode, realname;
	struct irc_msg *msg = res->data.ptr;
	// USER
	if (!pm_parse_step(&user_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	//  <user>' '
	r.data.ptr = &user;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <mode>' '
	r.data.ptr = &mode;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// "* :"
	char *mode_delim_data = "* :";
	str_t mode_delim_str = { .data = mode_delim_data, .len = 3 };
	pm_parser_t mode_delim = PM_STRING(&mode_delim_str);
	if (!pm_parse_step(&mode_delim, src, state, NULL))
		goto fail;
	// <realname>
	r.data.ptr = &realname;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool oper(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// OPER <name> <password>
	pm_result_t r;
	str_t name, password;
	struct irc_msg *msg = res->data.ptr;
	// OPER
	if (!pm_parse_step(&oper_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <name>' '
	r.data.ptr = &name;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <realname>
	r.data.ptr = &password;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool mode_user(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// MODE <nickname> <modes>
	pm_result_t r;
	str_t nickname, modes;
	struct irc_msg *msg = res->data.ptr;
	// MODE
	if (!pm_parse_step(&mode_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <nickname>' '
	r.data.ptr = &nickname;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <modes>
	r.data.ptr = &modes;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool service(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// SERVICE <nickname> <reserved> <distribution> <type> <reserved> :<info>
	pm_result_t r;
	str_t nickname, distribution, type, info;
	struct irc_msg *msg = res->data.ptr;
	// SERVICE
	if (!pm_parse_step(&service_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <nickname>' '
	r.data.ptr = &nickname;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, state, NULL))
		goto fail;
	// <distribution>' '
	r.data.ptr = &distribution;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <type>' '
	r.data.ptr = &type;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <reserved>' '
	if (!pm_parse_step(&pm_until_space, src, state, NULL))
		goto fail;
	// ':'
	if (!pm_parse_step(&colon, src, state, NULL))
		goto fail;
	// <info>
	r.data.ptr = &info;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool quit(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// QUIT[ :<msg>]
	pm_result_t r;
	str_t quit_msg;
	struct irc_msg *msg = res->data.ptr;
	// QUIT
	if (!pm_parse_step(&quit_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto no_msg;
	// ':'
	if (!pm_parse_step(&colon, src, state, NULL))
		goto no_msg;
	// <msg>
	r.data.ptr = &quit_msg;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool squit(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// SQUIT <server> :<comment>
	pm_result_t r;
	str_t server, comment;
	struct irc_msg *msg = res->data.ptr;
	// SQUIT
	if (!pm_parse_step(&service_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <server>' '
	r.data.ptr = &server;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// ':'
	if (!pm_parse_step(&colon, src, state, NULL))
		goto fail;
	// <comment>
	r.data.ptr = &comment;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool join_with_key(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// JOIN <channel>[ <key>]
	pm_result_t r;
	str_t channel, key;
	struct irc_msg *msg = res->data.ptr;
	// JOIN
	if (!pm_parse_step(&join_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <channel>[' ']
	r.data.ptr = &channel;
	if (!pm_parse_step(&pm_until_space, src, state, &r))
		goto fail;
	// <key>
	r.data.ptr = &key;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool join_no_key(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	// JOIN <channel>[ <key>]
	pm_result_t r;
	str_t channel;
	struct irc_msg *msg = res->data.ptr;
	// JOIN
	if (!pm_parse_step(&join_cmd, src, state, NULL))
		goto fail;
	// ' '
	if (!pm_parse_step(&pm_space, src, state, NULL))
		goto fail;
	// <channel>
	r.data.ptr = &channel;
	if (!pm_parse_step(&pm_trail, src, state, &r))
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
bool join(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	static pm_parser_t joins[2] = { PM_FN(join_with_key), PM_FN(join_no_key) };
	static pm_parser_t parser = PM_OR(joins);
	return pm_parse_step(&parser, src, state, res);
}

static
bool part(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool mode_channel(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool topic(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool names(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool list(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool invite(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool kick(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool privmsg(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool notice(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool motd(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool lusers(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool version(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool stats(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool links(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool time(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool connect(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool trace(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool admin(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool info(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool servlist(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool squery(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool who(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool whois(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool whowas(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool kill(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool ping(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool pong(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool error(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool away(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool rehash(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool die(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool restart(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool summon(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool users(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool wallops(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool userhost(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool ison(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

static
bool numeric(const pm_data_t d, const str_t *src, pm_state_t *state, pm_result_t *res)
{
	return false;
}

bool irc_parse(const str_t *line, struct irc_msg *msg)
{
	pm_result_t res = { .data.ptr = msg };
	static pm_parser_t msgs_arr[IRC_CMD_SIZE] = {
		[IRC_PASS] = PM_FN(pass),
		[IRC_NICK] = PM_FN(nick),
		[IRC_USER] = PM_FN(user),
		[IRC_OPER] = PM_FN(oper),
		[IRC_MODE_USER] = PM_FN(mode_user),
		[IRC_SERVICE] = PM_FN(service),
		[IRC_QUIT] = PM_FN(quit),
		[IRC_SQUIT] = PM_FN(squit),
		[IRC_JOIN] = PM_FN(join),
		[IRC_PART] = PM_FN(part),
		[IRC_MODE_CHANNEL] = PM_FN(mode_channel),
		[IRC_TOPIC] = PM_FN(topic),
		[IRC_NAMES] = PM_FN(names),
		[IRC_LIST] = PM_FN(list),
		[IRC_INVITE] = PM_FN(invite),
		[IRC_KICK] = PM_FN(kick),
		[IRC_PRIVMSG] = PM_FN(privmsg),
		[IRC_NOTICE] = PM_FN(notice),
		[IRC_MOTD] = PM_FN(motd),
		[IRC_LUSERS] = PM_FN(lusers),
		[IRC_VERSION] = PM_FN(version),
		[IRC_STATS] = PM_FN(stats),
		[IRC_LINKS] = PM_FN(links),
		[IRC_TIME] = PM_FN(time),
		[IRC_CONNECT] = PM_FN(connect),
		[IRC_TRACE] = PM_FN(trace),
		[IRC_ADMIN] = PM_FN(admin),
		[IRC_INFO] = PM_FN(info),
		[IRC_SERVLIST] = PM_FN(servlist),
		[IRC_SQUERY] = PM_FN(squery),
		[IRC_WHO] = PM_FN(who),
		[IRC_WHOIS] = PM_FN(whois),
		[IRC_WHOWAS] = PM_FN(whowas),
		[IRC_KILL] = PM_FN(kill),
		[IRC_PING] = PM_FN(ping),
		[IRC_PONG] = PM_FN(pong),
		[IRC_ERROR] = PM_FN(error),
		[IRC_AWAY] = PM_FN(away),
		[IRC_REHASH] = PM_FN(rehash),
		[IRC_DIE] = PM_FN(die),
		[IRC_RESTART] = PM_FN(restart),
		[IRC_SUMMON] = PM_FN(summon),
		[IRC_USERS] = PM_FN(users),
		[IRC_WALLOPS] = PM_FN(wallops),
		[IRC_USERHOST] = PM_FN(userhost),
		[IRC_ISON] = PM_FN(ison),
		[IRC_NUMERIC] = PM_FN(numeric),
	};
	static pm_parsers_t msgs_par = { .data = msgs_arr, .len = IRC_CMD_SIZE };
	static pm_parser_t msgs = PM_CHOICE_TRY(&msgs_par);
	return pm_parse(&msgs, line, &res);
}

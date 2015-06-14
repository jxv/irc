#ifndef IRC_H
#define IRC_H

#include <stdbool.h>
#include <str.h>

enum irc_sender {
	IRC_SENDER_YOU,
	IRC_SENDER_USER,
	IRC_SENDER_SERVER,
};

typedef enum irc_sender irc_sender_t;

struct irc_sender_user {
	str_t nickname;
	optstr_t username;
	optstr_t servername;
};

struct irc_sender_server {
	str_t name;
};

enum irc_cmd {
	// Connection Registration
	IRC_PASS,
	IRC_NICK,
	IRC_USER,
	IRC_OPER,
	IRC_MODE_USER,
	IRC_SERVICE,
	IRC_QUIT,
	IRC_SQUIT,
	// Channel operations
	IRC_JOIN,
	IRC_PART,
	IRC_MODE_CHANNEL,
	IRC_TOPIC,
	IRC_NAMES,
	IRC_LIST,
	IRC_INVITE,
	IRC_KICK,
	// Sending messages
	IRC_PRIVMSG,
	IRC_NOTICE,
	// Server queries and commands
	IRC_MOTD,
	IRC_LUSERS,
	IRC_VERSION,
	IRC_STATS,
	IRC_LINKS,
	IRC_TIME,
	IRC_CONNECT,
	IRC_TRACE,
	IRC_ADMIN,
	IRC_INFO,
	// Service Query and Commands
	IRC_SERVLIST,
	IRC_SQUERY,
	// User based queries
	IRC_WHO,
	IRC_WHOIS,
	IRC_WHOWAS,
	// Misc. messages
	IRC_KILL,
	IRC_PING,
	IRC_PONG,
	IRC_ERROR,
	// Optional features
	IRC_AWAY,
	IRC_REHASH,
	IRC_DIE,
	IRC_RESTART,
	IRC_SUMMON,
	IRC_USERS,
	IRC_WALLOPS,
	IRC_USERHOST,
	IRC_ISON,
	// Replies
	IRC_NUMERIC, // Check number
};

#define IRC_CMD_SIZE (IRC_NUMERIC+1)

typedef enum irc_cmd irc_cmd_t;

struct irc_pass {
	str_t password;
};

struct irc_nick {
	str_t nickname;
};

struct irc_user {
	str_t user;
	str_t mode;
	str_t realname;
};

struct irc_oper {
	str_t name;
	str_t password;
};

struct irc_mode_user {
	str_t nickname;
	str_t modes;
};

struct irc_service {
	str_t nickname;
	str_t distribution;
	str_t type;
	str_t info;
};

struct irc_quit {
	optstr_t msg;
};

struct irc_squit {
	str_t server;
	str_t comment;
};

struct irc_join {
	str_t channel;
	optstr_t key;
};

struct irc_part {
	str_t channel;
	optstr_t msg;
};

struct irc_mode_channel {
	str_t channel;
	bool crement;
	optstr_t modes;
	optstr_t params;
};

struct irc_topic {
	str_t channel;
	optstr_t topic;
};

struct irc_names {
	str_t channel; // [, channel]
	optstr_t target;
};

struct irc_list {
	str_t channel; // [, channel]
	optstr_t target;
};

struct irc_invite {
	str_t nickname;
	str_t channel;
};

struct irc_kick {
	str_t channel; // [, channel]
	str_t user; // [, user]
	optstr_t comment;
};

struct irc_privmsg {
	str_t target;
	str_t msg;
};

struct irc_notice {
	str_t target;
	str_t msg;
};

struct irc_motd {
	optstr_t target;
};

struct irc_lusers {
	str_t mask;
	optstr_t target;
};

struct irc_version {
	optstr_t target;
};

struct irc_stats {
	optstr_t query;
	optstr_t target;
};

struct irc_links {
	optstr_t remote_server;
	optstr_t server_mask;
};

struct irc_time {
	str_t target;
};

struct irc_connect {
	str_t target;
	str_t port;
	optstr_t remote_server;
};

struct irc_trace {
	optstr_t target;
};

struct irc_admin {
	optstr_t target;
};

struct irc_info {
	optstr_t target;
};

struct irc_servlist {
	optstr_t mask;
	optstr_t type;
};

struct irc_squery {
	str_t service_name;
	str_t msg;
};

struct irc_who {
	optstr_t mask;
	bool o;
};

struct irc_whois {
	optstr_t target;
	str_t mask; // [mask]
};

struct irc_whowas {
	str_t nickname; // [, nickname]
	optstr_t count;
	optstr_t target;
};

struct irc_kill {
	str_t nickname;
	str_t comment;
};

struct irc_ping {
	str_t server0;
	optstr_t server1;
};

struct irc_pong {
	str_t server0;
	optstr_t server1;
};

struct irc_error {
	str_t msg;
};

struct irc_away {
	optstr_t msg;
};

struct irc_summon {
	str_t user;
	optstr_t target;
	optstr_t channel;
};

struct irc_users {
	optstr_t target;
};

struct irc_wallops {
	str_t msg;
};

struct irc_userhost {
	optstr_t nicknames;
};

struct irc_ison {
	optstr_t nicknames;
};

struct irc_numeric {
	int val;
};

struct irc_msg {
	irc_sender_t sender;
	union {
		struct irc_sender_user sender_user;
		struct irc_sender_server sender_server;
	};
	irc_cmd_t cmd;
	union {
		struct irc_pass pass;
		struct irc_nick nick;
		struct irc_user user;
		struct irc_oper oper;
		struct irc_mode_user mode_user;
		struct irc_service service;
		struct irc_quit quit;
		struct irc_squit squit;
		struct irc_join join;
		struct irc_part part;
		struct irc_mode_channel mode_channel;
		struct irc_topic topic;
		struct irc_names names;
		struct irc_list list;
		struct irc_invite invite;
		struct irc_kick kick;
		struct irc_privmsg privmsg;
		struct irc_notice notice;
		struct irc_motd motd;
		struct irc_lusers lusers;
		struct irc_version version;
		struct irc_stats stats;
		struct irc_links links;
		struct irc_time time;
		struct irc_connect connect;
		struct irc_trace trace;
		struct irc_admin admin;
		struct irc_info info;
		struct irc_servlist servlist;
		struct irc_squery squery;
		struct irc_who who;
		struct irc_whois whois;
		struct irc_whowas whowas;
		struct irc_kill kill;
		struct irc_ping ping;
		struct irc_pong pong;
		struct irc_error error;
		struct irc_away away;
		struct irc_summon summon;
		struct irc_users users;
		struct irc_wallops wallops;
		struct irc_userhost userhost;
		struct irc_ison ison;
		struct irc_numeric numeric;
	};
};

typedef struct irc_msg irc_msg_t;

bool irc_parse(const str_t *line, irc_msg_t *msg);

#endif

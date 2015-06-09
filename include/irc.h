#ifndef IRC_H
#define IRC_H

#include <stdbool.h>
#include <str.h>

struct irc_str {
	char *data;
	int len;
};

struct irc_opt_str {
	bool exist;
	struct irc_str str;
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

struct irc_pass {
	struct irc_str password;
};

struct irc_nick {
	struct irc_str nickname;
};

struct irc_user {
	struct irc_str user;
	struct irc_str mode;
	struct irc_str realname;
};

struct irc_oper {
	struct irc_str name;
	struct irc_str password;
};

struct irc_mode_user {
	struct irc_str nickname;
	struct irc_str modes;
};

struct irc_service {
	struct irc_str nickname;
	struct irc_str distribution;
	struct irc_str type;
	struct irc_str info;
};

struct irc_quit {
	struct irc_opt_str msg;
};

struct irc_squit {
	struct irc_str server;
	struct irc_str comment;
};

struct irc_join {
	struct irc_str channel;
	struct irc_opt_str key;
};

struct irc_part {
	struct irc_str channel;
	struct irc_opt_str msg;
};

struct irc_mode_channel {
	struct irc_str channel;
	bool crement;
	struct irc_opt_str modes;
	struct irc_opt_str params;
};

struct irc_topic {
	struct irc_str channel;
	struct irc_opt_str topic;
};

struct irc_names {
	struct irc_str channel; // [, channel]
	struct irc_opt_str target;
};

struct irc_list {
	struct irc_str channel; // [, channel]
	struct irc_opt_str target;
};

struct irc_invite {
	struct irc_str nickname;
	struct irc_str channel;
};

struct irc_kick {
	struct irc_str channel; // [, channel]
	struct irc_str user; // [, user]
	struct irc_opt_str comment;
};

struct irc_privmsg {
	struct irc_str target;
	struct irc_str msg;
};

struct irc_notice {
	struct irc_str target;
	struct irc_str msg;
};

struct irc_motd {
	struct irc_opt_str target;
};

struct irc_lusers {
	struct irc_str mask;
	struct irc_opt_str target;
};

struct irc_version {
	struct irc_opt_str target;
};

struct irc_stats {
	struct irc_opt_str query;
	struct irc_opt_str target;
};

struct irc_links {
	struct irc_opt_str remote_server;
	struct irc_opt_str server_mask;
};

struct irc_time {
	struct irc_str target;
};

struct irc_connect {
	struct irc_str target;
	struct irc_str port;
	struct irc_opt_str remote_server;
};

struct irc_trace {
	struct irc_opt_str target;
};

struct irc_admin {
	struct irc_opt_str target;
};

struct irc_info {
	struct irc_opt_str target;
};

struct irc_servlist {
	struct irc_opt_str mask;
	struct irc_opt_str type;
};

struct irc_squery {
	struct irc_str service_name;
	struct irc_str msg;
};

struct irc_who {
	struct irc_opt_str mask;
	bool o;
};

struct irc_whois {
	struct irc_opt_str target;
	struct irc_str mask; // [mask]
};

struct irc_whowas {
	struct irc_str nickname; // [, nickname]
	struct irc_opt_str count;
	struct irc_opt_str target;
};

struct irc_kill {
	struct irc_str nickname;
	struct irc_str comment;
};

struct irc_ping {
	struct irc_str server0;
	struct irc_opt_str server1;
};

struct irc_pong {
	struct irc_str server0;
	struct irc_opt_str server1;
};

struct irc_error {
	struct irc_str msg;
};

struct irc_away {
	struct irc_opt_str msg;
};

struct irc_summon {
	struct irc_str user;
	struct irc_opt_str target;
	struct irc_opt_str channel;
};

struct irc_users {
	struct irc_opt_str target;
};

struct irc_wallops {
	struct irc_str msg;
};

struct irc_userhost {
	struct irc_opt_str nicknames;
};

struct irc_ison {
	struct irc_opt_str nicknames;
};

struct irc_numeric {
	int val;
};

struct irc_msg {
	enum irc_cmd cmd;
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

bool irc_parse(const str_t *line, struct irc_msg *msg);

#endif

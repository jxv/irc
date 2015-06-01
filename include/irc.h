#ifndef IRC_H
#define IRC_H

#include <stdbool.h>

struct irc_str {
	char *data;
	int len;
};

struct irc_opt_str {
	bool exist;
	struct irc_str str;
};

enum irc_cmd {
	IRC_PASS,
	IRC_NICK,
	IRC_USER,
	IRC_OPER,
	IRC_MODE_USER,
	//IRC_MODE_CHANNEL,
	IRC_SERVICE,
	IRC_QUIT,
	IRC_SQUIT,

	IRC_JOIN,
	IRC_PART,
	IRC_TOPIC,
	IRC_NAMES,
	IRC_LIST,
	IRC_INVITE,
	IRC_KICK,
	
	IRC_PRIVMSG,
	IRC_NOTICE,

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
	IRC_SERVLIST,
	IRC_SQUERY,

	IRC_WHO,
	IRC_WHOIS,
	IRC_WHOWAS,
	IRC_KILL,
	IRC_PING,
	IRC_PONG,
	IRC_ERROR,

	IRC_AWAY,
	IRC_REHASH,
	IRC_DIE,
	IRC_RESTART,
	IRC_SUMMON,
	IRC_USERS,
	IRC_WALLOPS,
	IRC_USERHOST,
	IRC_ISON,
	IRC_NUMERIC, // Check number
};

struct irc_msg {
	enum irc_cmd cmd;
	union {
		struct { struct irc_str password; } pass;
		struct { struct irc_str nickname; } nick;
		struct { struct irc_str user, mode, realname; } user;
		struct { struct irc_str name, password; } oper;
		struct { struct irc_str nickname, modes; } mode_user;
		struct { struct irc_str nickname, reserved0, distribution, type, reserved1, info; } service;
		struct { struct irc_opt_str msg; } quit;
		struct { struct irc_str server, comment; } squit;

		struct { struct irc_str channel; struct irc_opt_str channels, keys; } join;
		struct { struct irc_str channel; struct irc_opt_str channels, msg; } part;
		struct { struct irc_str channel; bool crement; struct irc_opt_str modes, params; } mode_channel;
		struct { struct irc_str channel; struct irc_opt_str topic; } topic;
		struct { struct irc_str channel; struct irc_opt_str channels, target; } names;
		struct { struct irc_str channel; struct irc_opt_str channels, target; } list;
		struct { struct irc_str nickname, channel; } invite;
		struct { struct irc_str channel; struct irc_opt_str channels; struct irc_str user; struct irc_opt_str users, comment; } kick;

		struct { struct irc_str target, msg; } privmsg;
		struct { struct irc_str target, msg; } notice;

		struct { struct irc_opt_str target; } motd;
		struct { struct irc_str mask; struct irc_opt_str target; } lusers;
		struct { struct irc_opt_str target; } version;
		struct { struct irc_opt_str query, target; } stats;
		struct { struct irc_opt_str remote_server, server_mask; } links;
		struct { struct irc_str target; } time;
		struct { struct irc_str target, port; struct irc_opt_str remote_server; } connect;
		struct { struct irc_opt_str target; } trace;
		struct { struct irc_opt_str target; } admin;
		struct { struct irc_opt_str target; } info;
		struct { struct irc_opt_str mask, type; } servlist;
		struct { struct irc_str service_name, msg; } squery;

		struct { struct irc_opt_str mask; bool o; } who;
		struct { struct irc_opt_str target; struct irc_str mask; struct irc_opt_str masks; } whois;
		struct { struct irc_str nickname; struct irc_opt_str nicknames, count, target; } whowas;
		struct { struct irc_str nickname, comment; } kill;
		struct { struct irc_str server0; struct irc_opt_str server1; } ping;
		struct { struct irc_str msg; } error;

		struct { struct irc_opt_str msg; } away;
		// rehash
		// die
		// restart
		struct { struct irc_str user; struct irc_opt_str target, channel; } summon;
		struct { struct irc_opt_str target; } users;
		struct { struct irc_str msg; } wallops;
		struct { struct irc_opt_str nicknames; } userhost;
		struct { struct irc_opt_str nicknames; } ison;
		struct { int val; } numeric;
	};
};

#endif

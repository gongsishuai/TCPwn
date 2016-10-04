/******************************************************************************
 * Author: Samuel Jero <sjero@purdue.edu>
******************************************************************************/
#ifndef _TCP_H
#define _TCP_H

#include "proto.h"
#include <netinet/tcp.h>

#define STATE_UNKNOWN 0
#define STATE_INIT 1
#define STATE_SLOW_START 2
#define STATE_CONG_AVOID 3
#define STATE_FAST_RECOV 4
#define STATE_RTO 5
#define STATE_END 6

#define INTERVAL 10

#define DELAYED_ACK true

class TCP: public Proto {
	public:
		TCP();
		~TCP();
		virtual void new_packet(pkt_info pk, Message hdr);
		virtual bool start();
		virtual bool stop();
		virtual bool isRunning() {return running || thread_running;}
		virtual bool hasIPProto(int num) {return num == 6;}

	private:
		static void* thread_run(void* arg);
		void run();
		void updateClassicCongestionControl(Message hdr);
		void processClassicCongestionControl();
		void printState(int oldstate, int state);

		pthread_rwlock_t lock;
		pthread_t thread;
		bool running;
		bool thread_running;
		bool thread_cleanup;

		unsigned int tcp1_port;
		unsigned int tcp1_seq_low;
		unsigned int tcp1_seq_high;
		unsigned int tcp1_ack_low;
		unsigned int tcp1_ack_high;
		unsigned int tcp1_ack_hold;
		unsigned int tcp2_port;
		unsigned int tcp2_seq_low;
		unsigned int tcp2_seq_high;
		unsigned int tcp2_ack_low;
		unsigned int tcp2_ack_high;
		unsigned int tcp2_ack_hold;
		
		unsigned int tcp_data_pkts;
		unsigned int tcp_data_bytes;
		unsigned int tcp_ack_pkts;
		unsigned int tcp_ack_bytes;
		unsigned int tcp_ack_dup;
		unsigned int tcp_retransmits;
		int state;
		int old_state;
		int idle_periods;

		struct timeval last_packet;
		unsigned int train;
		bool bursty;
		pthread_mutex_t last_lock;
};

#endif

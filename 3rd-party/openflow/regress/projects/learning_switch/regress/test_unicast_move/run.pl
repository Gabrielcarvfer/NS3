#!/usr/bin/perl -w
# test_unicast_move

use strict;
use OF::Includes;

sub my_test {

	my %delta;

	# host A's MAC address is 00:00:00:00:00:01

	my $pkt_args = {
		DA     => "00:00:00:00:00:02",
		SA     => "00:00:00:00:00:01",
		src_ip => "192.168.0.40",
		dst_ip => "192.168.1.40",
		ttl    => 64,
		len    => 64
	};
	my $pkt = new NF2::IP_pkt(%$pkt_args);

	# send one packet; controller should learn MAC, add a flow
	#  entry, and send this packet out the other interfaces
	print "Sending now: \n";
	send_and_count( 'eth1', $pkt->packed, \%delta );
	expect_and_count( 'eth2', $pkt->packed, \%delta );
	expect_and_count( 'eth3', $pkt->packed, \%delta );
	expect_and_count( 'eth4', $pkt->packed, \%delta );

	# sleep as long as needed for the test to finish
	sleep 0.1;

	$pkt_args = {
		DA     => "00:00:00:00:00:01",
		SA     => "00:00:00:00:00:02",
		src_ip => "192.168.1.40",
		dst_ip => "192.168.0.40",
		ttl    => 64,
		len    => 64
	};
	$pkt = new NF2::IP_pkt(%$pkt_args);
	send_and_count( 'eth2', $pkt->packed, \%delta );
	expect_and_count( 'eth1', $pkt->packed, \%delta );
	sleep 0.1;

	#Now Host A Has Changed Location and Attached to p2
	#It will send a packet to p1 form its new location
	$pkt_args = {
		DA     => "00:00:00:00:00:02",
		SA     => "00:00:00:00:00:01",
		src_ip => "192.168.2.40",
		dst_ip => "192.168.1.40",
		ttl    => 64,
		len    => 64
	};
	$pkt = new NF2::IP_pkt(%$pkt_args);
	send_and_count( 'eth3', $pkt->packed, \%delta );
	expect_and_count( 'eth2', $pkt->packed, \%delta );
	sleep 0.1;

	# Now p1 sends something to Host A which is now attached to p2
	# we expect the switch to already updated its entry for Host A
	$pkt_args = {
		DA     => "00:00:00:00:00:01",
		SA     => "00:00:00:00:00:02",
		src_ip => "192.168.1.40",
		dst_ip => "192.168.2.40",
		ttl    => 64,
		len    => 64
	};
	$pkt = new NF2::IP_pkt(%$pkt_args);
	send_and_count( 'eth2', $pkt->packed, \%delta );
	expect_and_count( 'eth3', $pkt->packed, \%delta );

	return %delta;
}

run_learning_switch_test( \&my_test,  \@ARGV  );

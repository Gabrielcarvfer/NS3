#!/usr/bin/perl -w
# test_flow_stats

use strict;
use OF::Includes;

sub my_test {

	my ( $sock, $options_ref ) = @_;

	enable_flow_expirations( $ofp, $sock );

	my $port_base = $$options_ref{'port_base'};

	my $hdr_args = {
		version => get_of_ver(),
		type    => $enums{'OFPT_STATS_REQUEST'},
		length  => $ofp->sizeof('ofp_stats_request') + $ofp->sizeof('ofp_flow_stats_request'),        # should generate automatically!
		xid     => 0x00000000
	};

	my $match_args = {
		wildcards => 0x3ff,
		in_port   => 0,
		dl_src    => [],
		dl_dst    => [],
		dl_vlan   => 0,
		dl_type   => 0,
		nw_src    => 0,
		nw_dst    => 0,
		nw_proto  => 0,
		tp_src    => 0,
		tp_dst    => 0
	};

	my $stats_request_args = {
		header        => $hdr_args,
		type          => $enums{'OFPST_FLOW'},
		flags		  => 0
	};

	my $body_args = {
		match   	=> $match_args,
		table_id	=> 0xff, #match all tables		
	};

	my $body = $ofp->pack('ofp_flow_stats_request', $body_args );

	my $stats_request = $ofp->pack( 'ofp_stats_request', $stats_request_args );

	my $mesg = $stats_request . $body;

	# Send 'stats_request' message
	print $sock $mesg;

	# Should add timeout here - will crash if no reply
	my $recvd_mesg;
	sysread( $sock, $recvd_mesg, 1512 ) || die "Failed to receive message: $!";

	# Inspect  message
	my $msg_size = length($recvd_mesg);

	my $msg = $ofp->unpack( 'ofp_stats_reply', $recvd_mesg );

	#print HexDump ($recvd_mesg);
	print Dumper($msg);

	# Verify fields
	verify_header( $msg, 'OFPT_STATS_REPLY', $msg_size );
	
	#----------------------
	
	# add flow mod, send pkt
	{
	
		my $in_port_offset = 0;
		my $out_port_offset = 1;
		my $wildcards = 0x3ff;
		my $wait = 5;
	
		#$$options_ref{'send_delay'} = 5;
		
		forward_simple ( $ofp, $sock, $options_ref, $in_port_offset, $out_port_offset, $wildcards, 'any', 1);
	
#		my $in_port = $in_port_offset + $$options_ref{'port_base'};
#		my $out_port = $out_port_offset + $$options_ref{'port_base'};	
#	
#		my $test_pkt = get_default_black_box_pkt_len( $in_port, $out_port, $$options_ref{'pkt_len'} );
#		my $flow_mod_pkt =
#		  create_flow_mod_from_udp( $ofp, $test_pkt, $in_port, $out_port, $wait, $wildcards );
#	
#		print $sock $flow_mod_pkt;
#	
#		# Give OF switch time to process the flow mod
#		usleep($$options_ref{'send_delay'});
#	
#		nftest_send( "eth" . ($in_port_offset + 1), $test_pkt->packed );
	}

	sleep .1;
	
	
	# Send 'stats_request' message
	print $sock $mesg;

	# Should add timeout here - will crash if no reply
	my $recvd_mesg;
	sysread( $sock, $recvd_mesg, 1512 ) || die "Failed to receive message: $!";

	# Inspect  message
	my $msg_size = length($recvd_mesg);

	my $msg = $ofp->unpack( 'ofp_stats_reply', $recvd_mesg );

	#print HexDump ($recvd_mesg);
	print Dumper($msg);

	# Verify fields
	verify_header( $msg, 'OFPT_STATS_REPLY', $msg_size );
	

	#wait_for_flow_expired_all( $ofp, $sock, $options_ref );	
	
	
}

run_black_box_test( \&my_test, \@ARGV );


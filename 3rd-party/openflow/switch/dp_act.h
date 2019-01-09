/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford
 * Junior University
 *
 * We are making the OpenFlow specification and associated documentation
 * (Software) available for public use and benefit with the expectation
 * that others will use, modify and enhance the Software and contribute
 * those enhancements back to the community. However, since we would
 * like to make the Software available for broadest use, with as few
 * restrictions as possible permission is hereby granted, free of
 * charge, to any person obtaining a copy of this Software to deal in
 * the Software under the copyrights without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * The name and trademarks of copyright holder(s) may NOT be used in
 * advertising or publicity pertaining to the Software or any
 * derivatives without specific, written prior permission.
 */

#ifndef DP_ACT_H
#define DP_ACT_H 1

#include "openflow/openflow.h"
#include "switch-flow.h"
#include "datapath.h"

#define ACT_VALIDATION_OK ((uint16_t)-1)

// MAH: start
// make available
void do_output(struct datapath *dp, struct ofpbuf *buffer, int in_port,
          size_t max_len, int out_port, bool ignore_no_fwd);
void set_mpls_label_act(struct ofpbuf *buffer, const struct sw_flow_key *key,
						    const uint32_t label_out);
void set_mpls_exp_act(struct ofpbuf *buffer, const struct sw_flow_key *key,
					      const uint8_t exp);
// MAH: end

uint16_t validate_actions(struct datapath *, const struct sw_flow_key *,
		const struct ofp_action_header *, size_t);
void execute_actions(struct datapath *, struct ofpbuf *,
		struct sw_flow_key *, const struct ofp_action_header *,
		size_t action_len, int ignore_no_fwd);

#endif /* dp_act.h */

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/* cairo - a vector graphics library with display and print output
 *
 * Copyright © 2004 Keith Packard
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * The original code as contributed to the cairo library under
 * the dual license MPL+LGPL. We used the LGPL relicensing clause to
 * get a GPL version of this code which now lives here. This header is
 * unmodified other than the licensing clause.
 *
 * The Original Code is the cairo graphics library.
 *
 * The Initial Developer of the Original Code is Keith Packard
 *
 * Contributor(s):
 *	Keith R. Packard <keithp@keithp.com>
 *
 * Code changes for ns-3 from upstream are marked with `//PDB'
 */

#include "cairo-wideint-private.h"

/**
 * \file
 * \ingroup highprec
 * Implementation of the cairo_x functions which implement high precision arithmetic.
 */

#if HAVE_UINT64_T

const char * cairo_impl64 = "uint64_t";

#define _cairo_uint32s_to_uint64(h,l) ((uint64_t) (h) << 32 | (l))

cairo_uquorem64_t
_cairo_uint64_divrem (cairo_uint64_t num, cairo_uint64_t den)
{
    cairo_uquorem64_t	qr;

    qr.quo = num / den;
    qr.rem = num % den;
    return qr;
}

#else

const char * cairo_impl64 = "uint32_t";

cairo_uint64_t
_cairo_uint32_to_uint64 (uint32_t i)
{
    cairo_uint64_t	q;

    q.lo = i;
    q.hi = 0;
    return q;
}

cairo_int64_t
_cairo_int32_to_int64 (int32_t i)
{
    cairo_uint64_t	q;

    q.lo = i;
    q.hi = i < 0 ? -1 : 0;
    return q;
}

static cairo_uint64_t
_cairo_uint32s_to_uint64 (uint32_t h, uint32_t l)
{
    cairo_uint64_t	q;

    q.lo = l;
    q.hi = h;
    return q;
}

cairo_uint64_t
_cairo_uint64_add (cairo_uint64_t a, cairo_uint64_t b)
{
    cairo_uint64_t	s;

    s.hi = a.hi + b.hi;
    s.lo = a.lo + b.lo;
    if (s.lo < a.lo)
	s.hi++;
    return s;
}

cairo_uint64_t
_cairo_uint64_sub (cairo_uint64_t a, cairo_uint64_t b)
{
    cairo_uint64_t	s;

    s.hi = a.hi - b.hi;
    s.lo = a.lo - b.lo;
    if (s.lo > a.lo)
	s.hi--;
    return s;
}

#define uint32_lo(i)	((i) & 0xffff)
#define uint32_hi(i)	((i) >> 16)
#define uint32_carry16	((1) << 16)

cairo_uint64_t
_cairo_uint32x32_64_mul (uint32_t a, uint32_t b)
{
    cairo_uint64_t  s;

    uint16_t	ah, al, bh, bl;
    uint32_t	r0, r1, r2, r3;

    al = uint32_lo (a);
    ah = uint32_hi (a);
    bl = uint32_lo (b);
    bh = uint32_hi (b);

    r0 = (uint32_t) al * bl;
    r1 = (uint32_t) al * bh;
    r2 = (uint32_t) ah * bl;
    r3 = (uint32_t) ah * bh;

    r1 += uint32_hi(r0);    /* no carry possible */
    r1 += r2;		    /* but this can carry */
    if (r1 < r2)	    /* check */
	r3 += uint32_carry16;

    s.hi = r3 + uint32_hi(r1);
    s.lo = (uint32_lo (r1) << 16) + uint32_lo (r0);
    return s;
}

cairo_int64_t
_cairo_int32x32_64_mul (int32_t a, int32_t b)
{
    cairo_int64_t s;
    s = _cairo_uint32x32_64_mul ((uint32_t) a, (uint32_t) b);
    if (a < 0)
	s.hi -= b;
    if (b < 0)
	s.hi -= a;
    return s;
}

cairo_uint64_t
_cairo_uint64_mul (cairo_uint64_t a, cairo_uint64_t b)
{
    cairo_uint64_t	s;

    s = _cairo_uint32x32_64_mul (a.lo, b.lo);
    s.hi += a.lo * b.hi + a.hi * b.lo;
    return s;
}

cairo_uint64_t
_cairo_uint64_lsl (cairo_uint64_t a, int shift)
{
    if (shift >= 32)
    {
	a.hi = a.lo;
	a.lo = 0;
	shift -= 32;
    }
    if (shift)
    {
	a.hi = a.hi << shift | a.lo >> (32 - shift);
	a.lo = a.lo << shift;
    }
    return a;
}

cairo_uint64_t
_cairo_uint64_rsl (cairo_uint64_t a, int shift)
{
    if (shift >= 32)
    {
	a.lo = a.hi;
	a.hi = 0;
	shift -= 32;
    }
    if (shift)
    {
	a.lo = a.lo >> shift | a.hi << (32 - shift);
	a.hi = a.hi >> shift;
    }
    return a;
}

#define _cairo_uint32_rsa(a,n)	((uint32_t) (((int32_t) (a)) >> (n)))

cairo_int64_t
_cairo_uint64_rsa (cairo_int64_t a, int shift)
{
    if (shift >= 32)
    {
	a.lo = a.hi;
	a.hi = _cairo_uint32_rsa (a.hi, 31);
	shift -= 32;
    }
    if (shift)
    {
	a.lo = a.lo >> shift | a.hi << (32 - shift);
	a.hi = _cairo_uint32_rsa (a.hi, shift);
    }
    return a;
}

int
_cairo_uint64_lt (cairo_uint64_t a, cairo_uint64_t b)
{
    return (a.hi < b.hi ||
	    (a.hi == b.hi && a.lo < b.lo));
}

int
_cairo_uint64_eq (cairo_uint64_t a, cairo_uint64_t b)
{
    return a.hi == b.hi && a.lo == b.lo;
}

int
_cairo_int64_lt (cairo_int64_t a, cairo_int64_t b)
{
    if (_cairo_int64_negative (a) && !_cairo_int64_negative (b))
	return 1;
    if (!_cairo_int64_negative (a) && _cairo_int64_negative (b))
	return 0;
    return _cairo_uint64_lt (a, b);
}

cairo_uint64_t
_cairo_uint64_not (cairo_uint64_t a)
{
    a.lo = ~a.lo;
    a.hi = ~a.hi;
    return a;
}

cairo_uint64_t
_cairo_uint64_negate (cairo_uint64_t a)
{
    a.lo = ~a.lo;
    a.hi = ~a.hi;
    if (++a.lo == 0)
	++a.hi;
    return a;
}

/*
 * Simple bit-at-a-time divide.
 */
cairo_uquorem64_t
_cairo_uint64_divrem (cairo_uint64_t num, cairo_uint64_t den)
{
    cairo_uquorem64_t	qr;
    cairo_uint64_t	bit;
    cairo_uint64_t	quo;

    bit = _cairo_uint32_to_uint64 (1);

    /* normalize to make den >= num, but not overflow */
    while (_cairo_uint64_lt (den, num) && (den.hi & 0x80000000) == 0)
    {
	bit = _cairo_uint64_lsl (bit, 1);
	den = _cairo_uint64_lsl (den, 1);
    }
    quo = _cairo_uint32_to_uint64 (0);

    /* generate quotient, one bit at a time */
    while (bit.hi | bit.lo)
    {
	if (_cairo_uint64_le (den, num))
	{
	    num = _cairo_uint64_sub (num, den);
	    quo = _cairo_uint64_add (quo, bit);
	}
	bit = _cairo_uint64_rsl (bit, 1);
	den = _cairo_uint64_rsl (den, 1);
    }
    qr.quo = quo;
    qr.rem = num;
    return qr;
}

#endif /* !HAVE_UINT64_T */

cairo_quorem64_t
_cairo_int64_divrem (cairo_int64_t num, cairo_int64_t den)
{
    int			num_neg = _cairo_int64_negative (num);
    int			den_neg = _cairo_int64_negative (den);
    cairo_uquorem64_t	uqr;
    cairo_quorem64_t	qr;

    if (num_neg)
	num = _cairo_int64_negate (num);
    if (den_neg)
	den = _cairo_int64_negate (den);
    uqr = _cairo_uint64_divrem (num, den);
    if (num_neg)
	qr.rem = _cairo_int64_negate ((cairo_int64_t)uqr.rem);  //PDB cast
    else
	qr.rem = uqr.rem;
    if (num_neg != den_neg)
	qr.quo = (cairo_int64_t) _cairo_int64_negate ((cairo_int64_t)uqr.quo);  //PDB cast
    else
	qr.quo = (cairo_int64_t) uqr.quo;
    return qr;
}

#if HAVE_UINT128_T

const char * cairo_impl128 = "uint128_t";

cairo_uquorem128_t
_cairo_uint128_divrem (cairo_uint128_t num, cairo_uint128_t den)
{
    cairo_uquorem128_t	qr;

    qr.quo = num / den;
    qr.rem = num % den;
    return qr;
}

#else

const char * cairo_impl128 = "cairo_uint64_t";

cairo_uint128_t
_cairo_uint32_to_uint128 (uint32_t i)
{
    cairo_uint128_t	q;

    q.lo = _cairo_uint32_to_uint64 (i);
    q.hi = _cairo_uint32_to_uint64 (0);
    return q;
}

cairo_int128_t
_cairo_int32_to_int128 (int32_t i)
{
    cairo_int128_t	q;

    q.lo = _cairo_int32_to_int64 (i);
    q.hi = _cairo_int32_to_int64 (i < 0 ? -1 : 0);
    return q;
}

cairo_uint128_t
_cairo_uint64_to_uint128 (cairo_uint64_t i)
{
    cairo_uint128_t	q;

    q.lo = i;
    q.hi = _cairo_uint32_to_uint64 (0);
    return q;
}

cairo_int128_t
_cairo_int64_to_int128 (cairo_int64_t i)
{
    cairo_int128_t	q;

    q.lo = i;
    q.hi = _cairo_int32_to_int64 (_cairo_int64_negative(i) ? -1 : 0);
    return q;
}

cairo_uint128_t
_cairo_uint128_add (cairo_uint128_t a, cairo_uint128_t b)
{
    cairo_uint128_t	s;

    s.hi = _cairo_uint64_add (a.hi, b.hi);
    s.lo = _cairo_uint64_add (a.lo, b.lo);
    if (_cairo_uint64_lt (s.lo, a.lo))
	s.hi = _cairo_uint64_add (s.hi, _cairo_uint32_to_uint64 (1));
    return s;
}

cairo_uint128_t
_cairo_uint128_sub (cairo_uint128_t a, cairo_uint128_t b)
{
    cairo_uint128_t	s;

    s.hi = _cairo_uint64_sub (a.hi, b.hi);
    s.lo = _cairo_uint64_sub (a.lo, b.lo);
    if (_cairo_uint64_gt (s.lo, a.lo))
	s.hi = _cairo_uint64_sub (s.hi, _cairo_uint32_to_uint64(1));
    return s;
}

#if HAVE_UINT64_T

#define uint64_lo32(i)	((i) & 0xffffffff)
#define uint64_hi32(i)	((i) >> 32)
#define uint64_lo(i)	((i) & 0xffffffff)
#define uint64_hi(i)	((i) >> 32)
#define uint64_shift32(i)   ((i) << 32)
#define uint64_carry32	(((uint64_t) 1) << 32)

#else

#define uint64_lo32(i)	((i).lo)
#define uint64_hi32(i)	((i).hi)

static cairo_uint64_t
uint64_lo (cairo_uint64_t i)
{
    cairo_uint64_t  s;

    s.lo = i.lo;
    s.hi = 0;
    return s;
}

static cairo_uint64_t
uint64_hi (cairo_uint64_t i)
{
    cairo_uint64_t  s;

    s.lo = i.hi;
    s.hi = 0;
    return s;
}

static cairo_uint64_t
uint64_shift32 (cairo_uint64_t i)
{
    cairo_uint64_t  s;

    s.lo = 0;
    s.hi = i.lo;
    return s;
}

static const cairo_uint64_t uint64_carry32 = { 0, 1 };

#endif

cairo_uint128_t
_cairo_uint64x64_128_mul (cairo_uint64_t a, cairo_uint64_t b)
{
    cairo_uint128_t	s;
    uint32_t		ah, al, bh, bl;
    cairo_uint64_t	r0, r1, r2, r3;

    al = uint64_lo32 (a);
    ah = uint64_hi32 (a);
    bl = uint64_lo32 (b);
    bh = uint64_hi32 (b);

    r0 = _cairo_uint32x32_64_mul (al, bl);
    r1 = _cairo_uint32x32_64_mul (al, bh);
    r2 = _cairo_uint32x32_64_mul (ah, bl);
    r3 = _cairo_uint32x32_64_mul (ah, bh);

    r1 = _cairo_uint64_add (r1, uint64_hi (r0));    /* no carry possible */
    r1 = _cairo_uint64_add (r1, r2);	    	    /* but this can carry */
    if (_cairo_uint64_lt (r1, r2))		    /* check */
	r3 = _cairo_uint64_add (r3, uint64_carry32);

    s.hi = _cairo_uint64_add (r3, uint64_hi(r1));
    s.lo = _cairo_uint64_add (uint64_shift32 (r1),
				uint64_lo (r0));
    return s;
}

cairo_int128_t
_cairo_int64x64_128_mul (cairo_int64_t a, cairo_int64_t b)
{
    cairo_int128_t  s;
    s = _cairo_uint64x64_128_mul (_cairo_int64_to_uint64(a),
				  _cairo_int64_to_uint64(b));
    if (_cairo_int64_negative (a))
	s.hi = _cairo_uint64_sub (s.hi,
				  _cairo_int64_to_uint64 (b));
    if (_cairo_int64_negative (b))
	s.hi = _cairo_uint64_sub (s.hi,
				  _cairo_int64_to_uint64 (a));
    return s;
}

cairo_uint128_t
_cairo_uint128_mul (cairo_uint128_t a, cairo_uint128_t b)
{
    cairo_uint128_t	s;

    s = _cairo_uint64x64_128_mul (a.lo, b.lo);
    s.hi = _cairo_uint64_add (s.hi,
				_cairo_uint64_mul (a.lo, b.hi));
    s.hi = _cairo_uint64_add (s.hi,
				_cairo_uint64_mul (a.hi, b.lo));
    return s;
}

cairo_uint128_t
_cairo_uint128_lsl (cairo_uint128_t a, int shift)
{
    if (shift >= 64)
    {
	a.hi = a.lo;
	a.lo = _cairo_uint32_to_uint64 (0);
	shift -= 64;
    }
    if (shift)
    {
	a.hi = _cairo_uint64_add (_cairo_uint64_lsl (a.hi, shift),
				    _cairo_uint64_rsl (a.lo, (64 - shift)));
	a.lo = _cairo_uint64_lsl (a.lo, shift);
    }
    return a;
}

cairo_uint128_t
_cairo_uint128_rsl (cairo_uint128_t a, int shift)
{
    if (shift >= 64)
    {
	a.lo = a.hi;
	a.hi = _cairo_uint32_to_uint64 (0);
	shift -= 64;
    }
    if (shift)
    {
	a.lo = _cairo_uint64_add (_cairo_uint64_rsl (a.lo, shift),
				    _cairo_uint64_lsl (a.hi, (64 - shift)));
	a.hi = _cairo_uint64_rsl (a.hi, shift);
    }
    return a;
}

cairo_uint128_t
_cairo_uint128_rsa (cairo_int128_t a, int shift)
{
    if (shift >= 64)
    {
	a.lo = a.hi;
	a.hi = _cairo_uint64_rsa (a.hi, 64-1);
	shift -= 64;
    }
    if (shift)
    {
	a.lo = _cairo_uint64_add (_cairo_uint64_rsl (a.lo, shift),
				    _cairo_uint64_lsl (a.hi, (64 - shift)));
	a.hi = _cairo_uint64_rsa (a.hi, shift);
    }
    return a;
}

int
_cairo_uint128_lt (cairo_uint128_t a, cairo_uint128_t b)
{
    return (_cairo_uint64_lt (a.hi, b.hi) ||
	    (_cairo_uint64_eq (a.hi, b.hi) &&
	     _cairo_uint64_lt (a.lo, b.lo)));
}

int
_cairo_int128_lt (cairo_int128_t a, cairo_int128_t b)
{
    if (_cairo_int128_negative (a) && !_cairo_int128_negative (b))
	return 1;
    if (!_cairo_int128_negative (a) && _cairo_int128_negative (b))
	return 0;
    return _cairo_uint128_lt (a, b);
}

int
_cairo_uint128_eq (cairo_uint128_t a, cairo_uint128_t b)
{
    return (_cairo_uint64_eq (a.hi, b.hi) &&
	    _cairo_uint64_eq (a.lo, b.lo));
}

#if HAVE_UINT64_T
#define _cairo_msbset64(q)  (q & ((uint64_t) 1 << 63))
#else
#define _cairo_msbset64(q)  (q.hi & ((uint32_t) 1 << 31))
#endif

cairo_uquorem128_t
_cairo_uint128_divrem (cairo_uint128_t num, cairo_uint128_t den)
{
    cairo_uquorem128_t	qr;
    cairo_uint128_t	bit;
    cairo_uint128_t	quo;

    bit = _cairo_uint32_to_uint128 (1);

    /* normalize to make den >= num, but not overflow */
    while (_cairo_uint128_lt (den, num) && !_cairo_msbset64(den.hi))
    {
	bit = _cairo_uint128_lsl (bit, 1);
	den = _cairo_uint128_lsl (den, 1);
    }
    quo = _cairo_uint32_to_uint128 (0);

    /* generate quotient, one bit at a time */
    while (_cairo_uint128_ne (bit, _cairo_uint32_to_uint128(0)))
    {
	if (_cairo_uint128_le (den, num))
	{
	    num = _cairo_uint128_sub (num, den);
	    quo = _cairo_uint128_add (quo, bit);
	}
	bit = _cairo_uint128_rsl (bit, 1);
	den = _cairo_uint128_rsl (den, 1);
    }
    qr.quo = quo;
    qr.rem = num;
    return qr;
}

cairo_uint128_t
_cairo_uint128_negate (cairo_uint128_t a)
{
    a.lo = _cairo_uint64_not (a.lo);
    a.hi = _cairo_uint64_not (a.hi);
    return _cairo_uint128_add (a, _cairo_uint32_to_uint128 (1));
}

cairo_uint128_t
_cairo_uint128_not (cairo_uint128_t a)
{
    a.lo = _cairo_uint64_not (a.lo);
    a.hi = _cairo_uint64_not (a.hi);
    return a;
}

#endif /* !HAVE_UINT128_T */

cairo_quorem128_t
_cairo_int128_divrem (cairo_int128_t num, cairo_int128_t den)
{
    int			num_neg = _cairo_int128_negative (num);
    int			den_neg = _cairo_int128_negative (den);
    cairo_uquorem128_t	uqr;
    cairo_quorem128_t	qr;

    if (num_neg)
	num = _cairo_int128_negate (num);
    if (den_neg)
	den = _cairo_int128_negate (den);
    uqr = _cairo_uint128_divrem (num, den);
    if (num_neg)
	qr.rem = _cairo_int128_negate (uqr.rem);
    else
	qr.rem = uqr.rem;
    if (num_neg != den_neg)
	qr.quo = _cairo_int128_negate (uqr.quo);
    else
	qr.quo = uqr.quo;
    return qr;
}

/**
 * _cairo_uint_96by64_32x64_divrem:
 *
 * Compute a 32 bit quotient and 64 bit remainder of a 96 bit unsigned
 * dividend and 64 bit divisor.  If the quotient doesn't fit into 32
 * bits then the returned remainder is equal to the divisor, and the
 * quotient is the largest representable 64 bit integer.  It is an
 * error to call this function with the high 32 bits of `num' being
 * non-zero. */
cairo_uquorem64_t
_cairo_uint_96by64_32x64_divrem (cairo_uint128_t num,
				 cairo_uint64_t den)
{
    cairo_uquorem64_t result;
    cairo_uint64_t B = _cairo_uint32s_to_uint64 (1, 0);

    /* These are the high 64 bits of the *96* bit numerator.  We're
     * going to represent the numerator as xB + y, where x is a 64,
     * and y is a 32 bit number. */
    cairo_uint64_t x = _cairo_uint128_to_uint64 (_cairo_uint128_rsl(num, 32));

    /* Initialise the result to indicate overflow. */
    result.quo = _cairo_uint32s_to_uint64 (UINT_MAX, UINT_MAX);  //PDB cast
    result.rem = den;

    /* Don't bother if the quotient is going to overflow. */
    if (_cairo_uint64_ge (x, den)) {
	return /* overflow */ result;
    }

    if (_cairo_uint64_lt (x, B)) {
	/* When the final quotient is known to fit in 32 bits, then
	 * num < 2^64 if and only if den < 2^32. */
	return _cairo_uint64_divrem (_cairo_uint128_to_uint64 (num), den);
    }
    else {
	/* Denominator is >= 2^32. the numerator is >= 2^64, and the
	 * division won't overflow: need two divrems.  Write the
	 * numerator and denominator as
	 *
	 *	num = xB + y		x : 64 bits, y : 32 bits
	 *	den = uB + v		u, v : 32 bits
	 */
	uint32_t y = _cairo_uint128_to_uint32 (num);
	uint32_t u = uint64_hi32 (den);
	uint32_t v = _cairo_uint64_to_uint32 (den);

	/* Compute a lower bound approximate quotient of num/den
	 * from x/(u+1).  Then we have
	 *
	 * x	= q(u+1) + r	; q : 32 bits, r <= u : 32 bits.
	 *
	 * xB + y	= q(u+1)B	+ (rB+y)
	 *		= q(uB + B + v - v) + (rB+y)
	 *		= q(uB + v)	+ qB - qv + (rB+y)
	 *		= q(uB + v)	+ q(B-v) + (rB+y)
	 *
	 * The true quotient of num/den then is q plus the
	 * contribution of q(B-v) + (rB+y).  The main contribution
	 * comes from the term q(B-v), with the term (rB+y) only
	 * contributing at most one part.
	 *
	 * The term q(B-v) must fit into 64 bits, since q fits into 32
	 * bits on account of being a lower bound to the true
	 * quotient, and as B-v <= 2^32, we may safely use a single
	 * 64/64 bit division to find its contribution. */

	cairo_uquorem64_t quorem;
	cairo_uint64_t remainder; /* will contain final remainder */
	uint32_t quotient;	/* will contain final quotient. */
	uint32_t q;
	uint32_t r;

	/* Approximate quotient by dividing the high 64 bits of num by
	 * u+1. Watch out for overflow of u+1. */
	if (u+1) {
	    quorem = _cairo_uint64_divrem (x, _cairo_uint32_to_uint64 (u+1));
	    q = _cairo_uint64_to_uint32 (quorem.quo);
	    r = _cairo_uint64_to_uint32 (quorem.rem);
	}
	else {
	    q = uint64_hi32 (x);
	    r = _cairo_uint64_to_uint32 (x);
	}
	quotient = q;

	/* Add the main term's contribution to quotient.  Note B-v =
	 * -v as an uint32 (unless v = 0) */
	if (v)
	    quorem = _cairo_uint64_divrem (_cairo_uint32x32_64_mul (q, -(int32_t)v), den);  //PDB cast
	else
	    quorem = _cairo_uint64_divrem (_cairo_uint32s_to_uint64 (q, 0), den);
	quotient += _cairo_uint64_to_uint32 (quorem.quo);

	/* Add the contribution of the subterm and start computing the
	 * true remainder. */
	remainder = _cairo_uint32s_to_uint64 (r, y);
	if (_cairo_uint64_ge (remainder, den)) {
	    remainder = _cairo_uint64_sub (remainder, den);
	    quotient++;
	}

	/* Add the contribution of the main term's remainder. The
	 * funky test here checks that remainder + main_rem >= den,
	 * taking into account overflow of the addition. */
	remainder = _cairo_uint64_add (remainder, quorem.rem);
	if (_cairo_uint64_ge (remainder, den) ||
	    _cairo_uint64_lt (remainder, quorem.rem))
	{
	    remainder = _cairo_uint64_sub (remainder, den);
	    quotient++;
	}

	result.quo = _cairo_uint32_to_uint64 (quotient);
	result.rem = remainder;
    }
    return result;
}

cairo_quorem64_t
_cairo_int_96by64_32x64_divrem (cairo_int128_t num, cairo_int64_t den)
{
    int			num_neg = _cairo_int128_negative (num);
    int			den_neg = _cairo_int64_negative (den);
    cairo_uint64_t	nonneg_den;
    cairo_uquorem64_t	uqr;
    cairo_quorem64_t	qr;

    if (num_neg)
	num = _cairo_int128_negate (num);
    if (den_neg)
	nonneg_den = _cairo_int64_negate (den);
    else
	nonneg_den = den;

    uqr = _cairo_uint_96by64_32x64_divrem (num, nonneg_den);
    if (_cairo_uint64_eq (uqr.rem, _cairo_int64_to_uint64 (nonneg_den))) {
	/* bail on overflow. */
	qr.quo = _cairo_uint32s_to_uint64 (0x7FFFFFFF, UINT_MAX);  //PDB cast
	qr.rem = den;
	return qr;
    }

    if (num_neg)
	qr.rem = _cairo_int64_negate ((cairo_int64_t)uqr.rem);  //PDB cast
    else
	qr.rem = uqr.rem;
    if (num_neg != den_neg)
	qr.quo = _cairo_int64_negate ((cairo_int64_t)uqr.quo);  //PDB cast
    else
	qr.quo = uqr.quo;
    return qr;
}

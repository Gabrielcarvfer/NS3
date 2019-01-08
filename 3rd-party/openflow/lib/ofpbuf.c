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

#include <config.h>
#include "ofpbuf.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* Initializes 'b' as an empty ofpbuf that contains the 'allocated' bytes of
 * memory starting at 'base'.
 *
 * 'base' should ordinarily be the first byte of a region obtained from
 * malloc(), but in circumstances where it can be guaranteed that 'b' will
 * never need to be expanded or freed, it can be a pointer into arbitrary
 * memory. */
void
ofpbuf_use(struct ofpbuf *b, void *base, size_t allocated)
{
    b->base = b->data = base;
    b->allocated = allocated;
    b->size = 0;
    // MAH: start
    //b->l2 = b->l3 = b->l4 = b->l7 = NULL;
    b->l2 = b->l2_5 = b->l3 = b->l4 = b->l7 = NULL;
    // MAH: end
    b->next = NULL;
    b->private = NULL;
}

/* Initializes 'b' as an empty ofpbuf with an initial capacity of 'size'
 * bytes. */
void
ofpbuf_init(struct ofpbuf *b, size_t size)
{
    ofpbuf_use(b, size ? xmalloc(size) : NULL, size);
}

/* Frees memory that 'b' points to. */
void
ofpbuf_uninit(struct ofpbuf *b)
{
    if (b) {
        free(b->base);
    }
}

/* Frees memory that 'b' points to and allocates a new ofpbuf */
void
ofpbuf_reinit(struct ofpbuf *b, size_t size)
{
    ofpbuf_uninit(b);
    ofpbuf_init(b, size);
}

/* Creates and returns a new ofpbuf with an initial capacity of 'size'
 * bytes. */
struct ofpbuf *
ofpbuf_new(size_t size)
{
    struct ofpbuf *b = xmalloc(sizeof *b);
    ofpbuf_init(b, size);
    return b;
}

struct ofpbuf *
ofpbuf_clone(const struct ofpbuf *buffer)
{
    /* FIXME: reference counting. */
	// MAH: start
	// change the below to allocate the same amount of space as the original
    //struct ofpbuf *b = ofpbuf_new(buffer->size);
	struct ofpbuf *b = ofpbuf_new(buffer->allocated);
    // MAH: end
    ofpbuf_put(b, buffer->data, buffer->size);
    return b;
}

/* Frees memory that 'b' points to, as well as 'b' itself. */
void
ofpbuf_delete(struct ofpbuf *b)
{
    if (b) {
        ofpbuf_uninit(b);
        free(b);
    }
}

/* Returns the number of bytes of headroom in 'b', that is, the number of bytes
 * of unused space in ofpbuf 'b' before the data that is in use.  (Most
 * commonly, the data in a ofpbuf is at its beginning, and thus the ofpbuf's
 * headroom is 0.) */
size_t
ofpbuf_headroom(struct ofpbuf *b)
{
    return (char*)b->data - (char*)b->base;
}

/* Returns the number of bytes that may be appended to the tail end of ofpbuf
 * 'b' before the ofpbuf must be reallocated. */
size_t
ofpbuf_tailroom(struct ofpbuf *b)
{
    return (char*)ofpbuf_end(b) - (char*)ofpbuf_tail(b);
}

/* Ensures that 'b' has room for at least 'size' bytes at its tail end,
 * reallocating and copying its data if necessary. */
void
ofpbuf_prealloc_tailroom(struct ofpbuf *b, size_t size)
{
    if (size > ofpbuf_tailroom(b)) {
        size_t new_allocated = b->allocated + MAX(size, 64);
        void *new_base = xmalloc(new_allocated);
        uintptr_t base_delta = (char*)new_base - (char*)b->base;
        memcpy(new_base, b->base, b->allocated);
        free(b->base);
        b->base = new_base;
        b->allocated = new_allocated;
        b->data = (char*)b->data + base_delta;
        if (b->l2) {
            b->l2 = (char*)b->l2 + base_delta;
        }
        // MAH: start
        if (b->l2_5) {
			b->l2_5 = (char*)b->l2_5 + base_delta;
		}
        // MAH: end
        if (b->l3) {
            b->l3 = (char*)b->l3 + base_delta;
        }
        if (b->l4) {
            b->l4 = (char*)b->l4 + base_delta;
        }
        if (b->l7) {
            b->l7 = (char*)b->l7 + base_delta;
        }
    }
}

void
ofpbuf_prealloc_headroom(struct ofpbuf *b, size_t size)
{
    assert(size <= ofpbuf_headroom(b));
}

/* Appends 'size' bytes of data to the tail end of 'b', reallocating and
 * copying its data if necessary.  Returns a pointer to the first byte of the
 * new data, which is left uninitialized. */
void *
ofpbuf_put_uninit(struct ofpbuf *b, size_t size)
{
    void *p;
    ofpbuf_prealloc_tailroom(b, size);
    p = ofpbuf_tail(b);
    b->size += size;
    return p;
}

/* Appends 'size' zeroed bytes to the tail end of 'b'.  Data in 'b' is
 * reallocated and copied if necessary.  Returns a pointer to the first byte of
 * the data's location in the ofpbuf. */
void *
ofpbuf_put_zeros(struct ofpbuf *b, size_t size)
{
    void *dst = ofpbuf_put_uninit(b, size);
    memset(dst, 0, size);
    return dst;
}

/* Appends the 'size' bytes of data in 'p' to the tail end of 'b'.  Data in 'b'
 * is reallocated and copied if necessary.  Returns a pointer to the first
 * byte of the data's location in the ofpbuf. */
void *
ofpbuf_put(struct ofpbuf *b, const void *p, size_t size)
{
    void *dst = ofpbuf_put_uninit(b, size);
    memcpy(dst, p, size);
    return dst;
}

/* Reserves 'size' bytes of headroom so that they can be later allocated with
 * ofpbuf_push_uninit() without reallocating the ofpbuf. */
void
ofpbuf_reserve(struct ofpbuf *b, size_t size)
{
    assert(!b->size);
    ofpbuf_prealloc_tailroom(b, size);
    b->data = (char*)b->data + size;
}

void *
ofpbuf_push_uninit(struct ofpbuf *b, size_t size)
{
    ofpbuf_prealloc_headroom(b, size);
    b->data = (char*)b->data - size;
    b->size += size;
    return b->data;
}

void *
ofpbuf_push(struct ofpbuf *b, const void *p, size_t size)
{
    void *dst = ofpbuf_push_uninit(b, size);
    memcpy(dst, p, size);
    return dst;
}

/* If 'b' contains at least 'offset + size' bytes of data, returns a pointer to
 * byte 'offset'.  Otherwise, returns a null pointer. */
void *
ofpbuf_at(const struct ofpbuf *b, size_t offset, size_t size)
{
    return offset + size <= b->size ? (char *) b->data + offset : NULL;
}

/* Returns a pointer to byte 'offset' in 'b', which must contain at least
 * 'offset + size' bytes of data. */
void *
ofpbuf_at_assert(const struct ofpbuf *b, size_t offset, size_t size)
{
    assert(offset + size <= b->size);
    return ((char *) b->data) + offset;
}

/* Returns the byte following the last byte of data in use in 'b'. */
void *
ofpbuf_tail(const struct ofpbuf *b)
{
    return (char *) b->data + b->size;
}

/* Returns the byte following the last byte allocated for use (but not
 * necessarily in use) by 'b'. */
void *
ofpbuf_end(const struct ofpbuf *b)
{
    return (char *) b->base + b->allocated;
}

/* Clears any data from 'b'. */
void
ofpbuf_clear(struct ofpbuf *b)
{
    b->data = b->base;
    b->size = 0;
}

/* Removes 'size' bytes from the head end of 'b', which must contain at least
 * 'size' bytes of data.  Returns the first byte of data removed. */
void *
ofpbuf_pull(struct ofpbuf *b, size_t size)
{
    void *data = b->data;
    assert(b->size >= size);
    b->data = (char*)b->data + size;
    b->size -= size;
    return data;
}

/* If 'b' has at least 'size' bytes of data, removes that many bytes from the
 * head end of 'b' and returns the first byte removed.  Otherwise, returns a
 * null pointer without modifying 'b'. */
void *
ofpbuf_try_pull(struct ofpbuf *b, size_t size)
{
    return b->size >= size ? ofpbuf_pull(b, size) : NULL;
}


// MAH: start
// Pop (i.e. remove) size bytes from the buffer starting at
// offset bytes from the base
void
ofpbuf_pop(struct ofpbuf *b, size_t offset, size_t num_bytes)
{
	// allocate some scratch memory to store all the bytes
	// that come after data + offset + size
	size_t scratch_size;
	uint8_t *pop_pos;
	void *scratch;

	pop_pos = (uint8_t *)b->data + offset;
	scratch_size = b->size - (offset + num_bytes);
	scratch = xmalloc(scratch_size);

	memcpy(scratch, pop_pos + num_bytes, scratch_size);

	// now copy back the bytes in scratch to
	// the buffer at the position base + offset
	memcpy(pop_pos, scratch, scratch_size);

	// free scratch memory
	free(scratch);

	// adjust layer pointers
	if (b->l2 && (b->l2 > (void*)pop_pos)) {
		b->l2 = (char*)b->l2 - num_bytes;
	}
	if (b->l2_5 && (b->l2_5 > (void*)pop_pos)) {
		b->l2_5 = (char*)b->l2_5 - num_bytes;
	}
	if (b->l3 && (b->l3 > (void*)pop_pos)) {
		b->l3 = (char*)b->l3 - num_bytes;
	}
	if (b->l4 && (b->l4 > (void*)pop_pos)) {
		b->l4 = (char*)b->l4 - num_bytes;
	}
	if (b->l7 && (b->l7 > (void*)pop_pos)) {
		b->l7 = (char*)b->l7 - num_bytes;
	}

	// if l2_5 == l3, remove l2_5
	// XXX is this right and should we do it for the other layers?
	if (b->l2_5 == b->l3) {
		b->l2_5 = NULL;
	}


	// update the size variable to indicate we are using
	// num_bytes less bytes
	b->size -= num_bytes;
}
// MAH: end

// MAH: start
// Push (i.e. insert) size bytes from data into the buffer starting at offset
// bytes from the base
// returns non-zero value if not successful
// memory allocated (e.g. b->size + num_bytes <= b->allocated)
size_t
ofpbuf_push_at(struct ofpbuf *b, size_t offset, void *data, size_t num_bytes)
{
	// check that there is enough room
	size_t headroom, tailroom;
	size_t scratch_size;
	uint8_t *push_pos;
	void *scratch;

	push_pos = (uint8_t *)b->data + offset;
	headroom = (size_t)b->data - (size_t)b->base;
	tailroom = (size_t)b->allocated - b->size - headroom;
	// XXX printf("ofpbuf_push_at: headroom = %u, tailroom = %u, requested size = %u\n", headroom, tailroom, num_bytes);
	if (tailroom < num_bytes) return (size_t)-1; // return non-zero to indicate error

	// allocate some scratch memory to store all the bytes
	// that come after data + offset + size
	scratch_size = b->size - offset;
	scratch = xmalloc(scratch_size);

	// XXX printf("copy from %x %u bytes\n and store in scratch\n", ((size_t)b->data + offset), scratch_size);
	memcpy(scratch, push_pos, scratch_size);

	// now copy num_bytes from data into the buffer at position data + offset
	// XXX printf("copy data to %x %u bytes\n", (size_t)b->data + offset, num_bytes);
	memcpy(push_pos, data, num_bytes);

	// now copy back the bytes in scratch to
	// the buffer at the position base + offset
	// XXX printf("copy to %x %u bytes\n", (size_t)b->data + offset + num_bytes, scratch_size);
	memcpy(push_pos + num_bytes, scratch, scratch_size);

	// free scratch mem
	free(scratch);

	// adjust layer pointers
	if (b->l2 && (b->l2 <= (void*)push_pos)) {
		b->l2 = (char*)b->l2 + num_bytes;
	}
	if (b->l2_5 && (b->l2_5 <= (void*)push_pos)) {
		b->l2_5 = (char*)b->l2_5 + num_bytes;
	}
	if (b->l3 && (b->l3 <= (void*)push_pos)) {
		b->l3 = (char*)b->l3 + num_bytes;
	}
	if (b->l4 && (b->l4 <= (void*)push_pos)) {
		b->l4 = (char*)b->l4 + num_bytes;
	}
	if (b->l7 && (b->l7 <= (void*)push_pos)) {
		b->l7 = (char*)b->l7 + num_bytes;
	}

	// update the size variable to indicate we are using
	// num_bytes more bytes
	b->size += num_bytes;
	return 0;
}
// MAH: end

#!/usr/bin/env python3
## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

import cairo
import sys
import re
import gtk


## DataRange class
class DataRange:
    ## @var start
    #  start
    ## @var end
    #  end
    ## @var value
    #  value
    def __init__(self, start = 0, end = 0, value = ''):
        """! Initializer
        @param self this object
        @param start start
        @param end end
        @param value value
        @return none
        """
        self.start = start
        self.end = end
        self.value = value
## EventString class
class EventString:
    ## @var at
    #  at
    ## @var value
    #  value
    def __init__(self, at = 0, value = ''):
        """! Initializer
        @param self this object
        @param at you
        @param value value
        @return none
        """
        self.at = at
        self.value = value
## EventFloat class
class EventFloat:
    ## @var at
    #  at
    ## @var value
    #  value
    def __init__(self, at = 0, value = 0.0):
        """! Initializer
        @param self this object
        @param at you
        @param value value
        @return none
        """
        self.at = at
        self.value = value
## EventInt class
class EventInt:
    ## @var at
    #  at
    ## @var value
    #  value
    def __init__(self, at = 0, value = 0.0):
        """! Initializer
        @param self this object
        @param at you
        @param value value
        @return none
        """
        self.at = at
        self.value = value
def ranges_cmp(a, b):
    diff = a.start - b.start
    if diff < 0:
        return -1
    elif diff > 0:
        return +1
    else:
        return 0
def events_cmp(a, b):
    diff = a.at - b.at
    if diff < 0:
        return -1
    elif diff > 0:
        return +1
    else:
        return 0
## TimelineDataRange
class TimelineDataRange:
    ## @var name
    #  name
    ## @var ranges
    #  ranges
    def __init__(self, name = ''):
        """! Initializer
        @param self this object
        @param name name
        @return none
        """
        self.name = name
        self.ranges = []
        return
    def __search(self, key):
        """! Search
        @param self this object
        @param key key
        @return index if found or -1 if not found
        """
        l = 0
        u = len(self.ranges)-1
        while l <= u:
            i = int((l + u) / 2)
            if key >= self.ranges[i].start and key <= self.ranges[i].end:
                return i
            elif key < self.ranges[i].start:
                u = i - 1
            else:
                # key > self.ranges[i].end
                l = i + 1
        return - 1
    def add_range(self, range):
        """! Add range
        @param self this object
        @param range range
        @return none
        """
        self.ranges.append(range)
    def get_all(self):
        """! Get all ranges
        @param self this object
        @return the ranges
        """
        return self.ranges
    def get_ranges(self, start, end):
        """! Get selected ranges
        @param self this object
        @param start range start
        @param end range end
        @return the range or and empty list
        """
        s = self.__search(start)
        e = self.__search(end)
        if s == -1 and e == -1:
            return []
        elif s == -1:
            return self.ranges[0:e + 1]
        elif e == -1:
            return self.ranges[s:len(self.ranges)]
        else:
            return self.ranges[s:e + 1]
    def get_ranges_bounds(self, start, end):
        """! Get ranges bounds
        @param self this object
        @param start range start
        @param end range end
        @return range
        """
        s = self.__search(start)
        e = self.__search(end)
        if s == -1 and e == -1:
            return(0, 0)
        elif s == -1:
            return(0, e + 1)
        elif e == -1:
            return(s, len(self.ranges))
        else:
            return(s, e + 1)
    def sort(self):
        """! Sort ranges
        @param self this object
        @return none
        """
        self.ranges.sort(ranges_cmp)
    def get_bounds(self):
        """! Get bounds
        @param self this object
        @return the bounds
        """
        if len(self.ranges) > 0:
            lo = self.ranges[0].start
            hi = self.ranges[len(self.ranges)-1].end
            return(lo, hi)
        else:
            return(0, 0)
## TimelineEvent class
class TimelineEvent:
    ## @var name
    #  name
    ## @var events
    #  events
    def __init__(self, name = ''):
        """! Get ranges bounds
        @param self this object
        @param name name
        @return none
        """
        self.name = name
        self.events = []
    def __search(self, key):
        """! Search function
        @param self this object
        @param key the key
        @return event index
        """
        l = 0
        u = len(self.events)-1
        while l <= u:
            i = int((l + u) / 2)
            if key == self.events[i].at:
                return i
            elif key < self.events[i].at:
                u = i - 1
            else:
                # key > self.events[i].at
                l = i + 1
        return l
    def add_event(self, event):
        """! Add Event
        @param self this object
        @param event event to add
        @return none
        """
        self.events.append(event)
    def get_events(self, start, end):
        """! Get Events
        @param self this object
        @param start starting event
        @param end ending event
        @return the events
        """
        s = self.__search(start)
        e = self.__search(end)
        return self.events[s:e + 1]
    def get_events_bounds(self, start, end):
        """! Get Events Bounds
        @param self this object
        @param start starting event
        @param end ending event
        @return event bounds
        """
        s = self.__search(start)
        e = self.__search(end)
        return(s, e + 1)
    def sort(self):
        """! Sort function
        @param self this object
        @return none
        """
        self.events.sort(events_cmp)
    def get_bounds(self):
        """! Get Bounds
        @param self this object
        @return the bounds
        """
        if len(self.events) > 0:
            lo = self.events[0].at
            hi = self.events[-1].at
            return(lo, hi)
        else:
            return(0, 0)

## Timeline class
class Timeline:
    ## @var name
    #  name
    ## @var ranges
    #  ranges
    ## @var event_str
    #  event string
    ## @var event_int
    #  event int
    def __init__(self, name = ''):
        """! Initializer
        @param self this object
        @param name name
        @return none
        """
        self.ranges = []
        self.event_str = []
        self.event_int = []
        self.name = name
    def get_range(self, name):
        """! Get range
        @param self this object
        @param name name
        @return the range
        """
        for range in self.ranges:
            if range.name == name:
                return range
        timeline = TimelineDataRange(name)
        self.ranges.append(timeline)
        return timeline
    def get_event_str(self, name):
        """! Get Event String
        @param self this object
        @param name name
        @return the event string
        """
        for event_str in self.event_str:
            if event_str.name == name:
                return event_str
        timeline = TimelineEvent(name)
        self.event_str.append(timeline)
        return timeline
    def get_event_int(self, name):
        """! Get Event Int
        @param self this object
        @param name name
        @return eevent int
        """
        for event_int in self.event_int:
            if event_int.name == name:
                return event_int
        timeline = TimelineEvent(name)
        self.event_int.append(timeline)
        return timeline
    def get_ranges(self):
        """! Get Ranges
        @param self this object
        @return the ranges
        """
        return self.ranges
    def get_events_str(self):
        """! Get Events string
        @param self this object
        @return event string
        """
        return self.event_str
    def get_events_int(self):
        """! Get Events int
        @param self this object
        @return evrnt int
        """
        return self.event_int
    def sort(self):
        """! Sort the ranges and events
        @param self this object
        @return none
        """
        for range in self.ranges:
            range.sort()
        for event in self.event_int:
            event.sort()
        for event in self.event_str:
            event.sort()
    def get_bounds(self):
        """! Get Bounds
        @param self this object
        @return the bounds
        """
        lo = 0
        hi = 0
        for range in self.ranges:
            (range_lo, range_hi) = range.get_bounds()
            if range_lo < lo:
                lo = range_lo
            if range_hi > hi:
                hi = range_hi
        for event_str in self.event_str:
            (ev_lo, ev_hi) = event_str.get_bounds()
            if ev_lo < lo:
                lo = ev_lo
            if ev_hi > hi:
                hi = ev_hi
        for event_int in self.event_int:
            (ev_lo, ev_hi) = event_int.get_bounds()
            if ev_lo < lo:
                lo = ev_lo
            if ev_hi > hi:
                hi = ev_hi
        return(lo, hi)

## Timelines class
class Timelines:
    ## @var timelines
    #  timelines
    def __init__(self):
        """ Initializer
        @param self: this object
        """
        self.timelines = []
    def get(self, name):
        """! Get Timeline
        @param self this object
        @param name name
        @return the timeline for the name
        """
        for timeline in self.timelines:
            if timeline.name == name:
                return timeline
        timeline = Timeline(name)
        self.timelines.append(timeline)
        return timeline
    def get_all(self):
        """! Get All Timeline
        @param self this object
        @return all timelines
        """
        return self.timelines
    def sort(self):
        """! Sort the timelines
        @param self this object
        @return none
        """
        for timeline in self.timelines:
            timeline.sort()
    def get_bounds(self):
        """! Get Bounds
        @param self this object
        @return the bounds for all timelines
        """
        lo = 0
        hi = 0
        for timeline in self.timelines:
            (t_lo, t_hi) = timeline.get_bounds()
            if t_lo < lo:
                lo = t_lo
            if t_hi > hi:
                hi = t_hi
        return(lo, hi)
    def get_all_range_values(self):
        """! Get All Ranges
        @param self this object
        @return the keys for all ranges
        """
        range_values = {}
        for timeline in self.timelines:
            for ranges in timeline.get_ranges():
                for ran in ranges.get_all():
                    range_values[ran.value] = 1
        return range_values.keys()

## Color class
class Color:
    ## @var r
    #  red
    ## @var g
    #  green
    ## @var b
    #  blue
    def __init__(self, r = 0.0, g = 0.0, b = 0.0):
        """! Initializer
        @param self: this object
        @param r: red
        @param g: green
        @param b: blue
        @return none
        """
        self.r = r
        self.g = g
        self.b = b
    def set(self, r, g, b):
        """! Set color
        @param self: this object
        @param r: red
        @param g: green
        @param b: blue
        @return none
        """
        self.r = r
        self.g = g
        self.b = b

## Colors class
class Colors:
    ## @var __colors
    #  colors
    ## @var default_colors
    #  default colors
    ## XXX add more
    default_colors = [Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1), Color(1, 1, 0), Color(1, 0, 1), Color(0, 1, 1)]
    def __init__(self):
        """! Initializer
        @param self this object
        @return none
        """
        self.__colors = {}
    def add(self, name, color):
        """! Add
        @param self this object
        @param name name of the color
        @param color color value
        @return none
        """
        self.__colors[name] = color
    def lookup(self, name):
        """! Lookup name
        @param self this object
        @param name name
        @return named color
        """
        if not self.__colors.has_key(name):
            self.add(name, self.default_colors.pop())
        return self.__colors.get(name)

## TopLegendRenderer class
class TopLegendRenderer:
    ## @var __padding
    #  padding
    ## @var __legends
    #  legends
    ## @var __colors
    #  colors
    ## @var __width
    #  width
    ## @var __height
    #  height
    def __init__(self):
        """! Initializer
        @param self this object
        @return none
        """
        self.__padding = 10
    def set_padding(self, padding):
        """! Set padding 
        @param self this object
        @param padding padding
        @return none
        """
        self.__padding = padding
    def set_legends(self, legends, colors):
        """! Set padding 
        @param self this object
        @param legends legends
        @param colors colors
        @return none
        """
        self.__legends = legends
        self.__colors = colors
    def layout(self, width):
        """! Set padding 
        @param self this object
        @param width width
        @return none
        """
        self.__width = width
        surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 1, 1)
        ctx = cairo.Context(surface)
        line_height = 0
        total_height = self.__padding
        line_used = self.__padding
        for legend in self.__legends:
            (t_width, t_height) = ctx.text_extents(legend)[2:4]
            item_width = self.__padding + self.__padding + t_width + self.__padding
            item_height = t_height + self.__padding
            if item_height > line_height:
                line_height = item_height
            if line_used + item_width > self.__width:
                line_used = self.__padding + item_width
                total_height += line_height
            else:
                line_used += item_width
            x = line_used - item_width
        total_height += line_height
        self.__height = total_height

    def get_height(self):
        """! Set padding 
        @param self this object
        @return height
        """
        return self.__height
    def draw(self, ctx):
        """! Set padding 
        @param self this object
        @param ctx ctx
        @return none
        """
        i = 0
        line_height = 0
        total_height = self.__padding
        line_used = self.__padding
        for legend in self.__legends:
            (t_width, t_height) = ctx.text_extents(legend)[2:4]
            item_width = self.__padding + self.__padding + t_width + self.__padding
            item_height = t_height + self.__padding
            if item_height > line_height:
                line_height = item_height
            if line_used + item_width > self.__width:
                line_used = self.__padding + item_width
                total_height += line_height
            else:
                line_used += item_width
            x = line_used - item_width
            ctx.rectangle(x, total_height, self.__padding, self.__padding)
            ctx.set_source_rgb(0, 0, 0)
            ctx.set_line_width(2)
            ctx.stroke_preserve()
            ctx.set_source_rgb(self.__colors[i].r, 
                               self.__colors[i].g, 
                               self.__colors[i].b)
            ctx.fill()
            ctx.move_to(x + self.__padding*2, total_height + t_height)
            ctx.set_source_rgb(0, 0, 0)
            ctx.show_text(legend)
            i += 1

        return

## TimelinesRenderer class
class TimelinesRenderer:
    ## @var padding
    #  padding
    ## @var timelines
    #  timelines
    ## @var colors
    #  colors
    ## @var start
    #  start
    ## @var end
    #  end
    ## @var left_width
    #  left width
    ## @var right_width
    #  right width
    ## @var max_text_height
    #  maximum text height
    ## @var width
    #  width
    ## @var height
    #  height
    ## @var grey_background
    #  grey background
    def __init__(self):
        """! Initializer 
        @param self this object
        @return none
        """
        self.padding = 10
        return
    def get_height(self):
        """! Get Height 
        @param self this object
        @return height
        """
        return self.height
    def set_timelines(self, timelines, colors):
        """! Set Timelines 
        @param self this object
        @param timelines timelines
        @param colors colors
        @return none
        """
        self.timelines = timelines
        self.colors = colors
    def set_render_range(self, start, end):
        """! Set Render Range 
        @param self this object
        @param start start
        @param end end
        @return none
        """
        self.start = start
        self.end = end
    def get_data_x_start(self):
        """! Get Data X Start 
        @param self: this object
        @return X start
        """
        return self.padding / 2 + self.left_width + self.padding + self.right_width + self.padding / 2
    def layout(self, width):
        """! Get Data X Start 
        @param self this object
        @param width width
        @return none
        """
        surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 1, 1)
        ctx = cairo.Context(surface)
        max_text_height = ctx.text_extents("ABCDEFGHIJKLMNOPQRSTUVWXYZabcedefghijklmnopqrstuvwxyz0123456789")[3]

        left_width = 0
        right_width = 0
        left_n_lines = 0
        range_n = 0
        eventint_n = 0
        eventstr_n = 0
        for timeline in self.timelines.get_all():
            left_n_lines += 1
            t_width = ctx.text_extents(timeline.name)[2]
            left_width = max(left_width, t_width)
            for rang in timeline.get_ranges():
                t_width = ctx.text_extents(rang.name)[2]
                right_width = max(right_width, t_width)
                range_n += 1
            for events_int in timeline.get_events_int():
                t_width = ctx.text_extents(events_int.name)[2]
                right_width = max(right_width, t_width)
                eventint_n += 1
            for events_str in timeline.get_events_str():
                t_width = ctx.text_extents(events_str.name)[2]
                right_width = max(right_width, t_width)
                eventstr_n += 1

        left_height = left_n_lines * max_text_height + (left_n_lines - 1) * self.padding
        right_n_lines = range_n + eventint_n + eventstr_n
        right_height = (right_n_lines - 1) * self.padding + right_n_lines * max_text_height
        right_data_height = (eventint_n + eventstr_n) * (max_text_height + 5) + range_n * 10
        right_data_height += (right_n_lines - 1) * self.padding

        height = max(left_height, right_height)
        height = max(height, right_data_height)

        self.left_width = left_width
        self.right_width = right_width
        self.max_text_height = max_text_height
        self.width = width
        self.height = height + self.padding
    def draw_line(self, ctx, x, y, width, height):
        """! Draw Line 
        @param self this object
        @param ctx ctx
        @param x x
        @param y y
        @param width width
        @param height height
        @return none
        """
        ctx.move_to(x, y)
        ctx.rel_line_to(width, height)
        ctx.close_path()
        ctx.set_operator(cairo.OPERATOR_SOURCE)
        ctx.set_line_width(1.0)
        ctx.set_source_rgb(0, 0, 0)
        ctx.stroke()
    def draw_events(self, ctx, events, x, y, width, height):
        """! Draw Event 
        @param self this object
        @param ctx ctx
        @param events events
        @param x x
        @param y y
        @param width width
        @param height height
        @return none
        """
        if (self.grey_background % 2) == 0:
            ctx.rectangle(x, y - self.padding / 2, 
                          width, height + self.padding)
            ctx.set_source_rgb(0.9, 0.9, 0.9)
            ctx.fill()
        last_x_drawn = int(x)
        (lo, hi) = events.get_events_bounds(self.start, self.end)
        for event in events.events[lo:hi]:
            real_x = int(x + (event.at - self.start) * width / (self.end - self.start))
            if real_x > last_x_drawn + 2:
                ctx.rectangle(real_x, y, 1, 1)
                ctx.set_source_rgb(1, 0, 0)
                ctx.stroke()
                ctx.move_to(real_x, y + self.max_text_height)
                ctx.set_source_rgb(0, 0, 0)
                ctx.show_text(str(event.value))
                last_x_drawn = real_x
        self.grey_background += 1
    def draw_ranges(self, ctx, ranges, x, y, width, height):
        """! Draw Ranges 
        @param self this object
        @param ctx ctx
        @param ranges ranges
        @param x x
        @param y y
        @param width width
        @param height height
        @return none
        """
        if (self.grey_background % 2) == 0:
            ctx.rectangle(x, y - self.padding / 2, 
                          width, height + self.padding)
            ctx.set_source_rgb(0.9, 0.9, 0.9)
            ctx.fill()
        last_x_drawn = int(x - 1)
        (lo, hi) = ranges.get_ranges_bounds(self.start, self.end)
        for data_range in ranges.ranges[lo:hi]:
            s = max(data_range.start, self.start)
            e = min(data_range.end, self.end)
            x_start = int(x + (s - self.start) * width / (self.end - self.start))
            x_end = int(x + (e - self.start) * width / (self.end - self.start))
            if x_end > last_x_drawn:
                ctx.rectangle(x_start, y, x_end - x_start, 10)
                ctx.set_source_rgb(0, 0, 0)
                ctx.stroke_preserve()
                color = self.colors.lookup(data_range.value)
                ctx.set_source_rgb(color.r, color.g, color.b)
                ctx.fill()
                last_x_drawn = x_end

        self.grey_background += 1

    def draw(self, ctx):
        """! Draw
        @param self this object
        @param ctx ctx
        @return none
        """
        timeline_top = 0
        top_y = self.padding / 2
        left_x_start = self.padding / 2
        left_x_end = left_x_start + self.left_width
        right_x_start = left_x_end + self.padding
        right_x_end = right_x_start + self.right_width
        data_x_start = right_x_end + self.padding / 2
        data_x_end = self.width
        data_width = data_x_end - data_x_start
        cur_y = top_y
        self.draw_line(ctx, 0, 0, self.width, 0)
        self.grey_background = 1
        for timeline in self.timelines.get_all():
            (y_bearing, t_width, t_height) = ctx.text_extents(timeline.name)[1:4]
            ctx.move_to(left_x_start, cur_y + self.max_text_height - (t_height + y_bearing))
            ctx.show_text(timeline.name);
            for events_int in timeline.get_events_int():
                (y_bearing, t_width, t_height) = ctx.text_extents(events_int.name)[1:4]
                ctx.move_to(right_x_start, cur_y + self.max_text_height - (t_height + y_bearing))
                ctx.show_text(events_int.name)
                self.draw_events(ctx, events_int, data_x_start, cur_y, data_width, self.max_text_height + 5)
                cur_y += self.max_text_height + 5 + self.padding
                self.draw_line(ctx, right_x_start - self.padding / 2, cur_y - self.padding / 2, 
                               self.right_width + self.padding, 0)

            for events_str in timeline.get_events_str():
                (y_bearing, t_width, t_height) = ctx.text_extents(events_str.name)[1:4]
                ctx.move_to(right_x_start, cur_y + self.max_text_height - (t_height + y_bearing))
                ctx.show_text(events_str.name)
                self.draw_events(ctx, events_str, data_x_start, cur_y, data_width, self.max_text_height + 5)
                cur_y += self.max_text_height + 5 + self.padding
                self.draw_line(ctx, right_x_start - self.padding / 2, cur_y - self.padding / 2, 
                               self.right_width + self.padding, 0)
            for ranges in timeline.get_ranges():
                (y_bearing, t_width, t_height) = ctx.text_extents(ranges.name)[1:4]
                ctx.move_to(right_x_start, cur_y + self.max_text_height - (t_height + y_bearing))
                ctx.show_text(ranges.name)
                self.draw_ranges(ctx, ranges, data_x_start, cur_y, data_width, 10)
                cur_y += self.max_text_height + self.padding
                self.draw_line(ctx, right_x_start - self.padding / 2, cur_y - self.padding / 2, 
                               self.right_width + self.padding, 0)
            self.draw_line(ctx, 0, cur_y - self.padding / 2, 
                           self.width, 0)
        bot_y = cur_y - self.padding / 2
        self.draw_line(ctx, left_x_end + self.padding / 2, 0, 
                       0, bot_y)
        self.draw_line(ctx, right_x_end + self.padding / 2, 0, 
                       0, bot_y)
        return

## ScaleRenderer class
class ScaleRenderer:
    ## @var __top
    #  top
    ## @var __lo
    #  lo
    ## @var __hi
    #  hi
    ## @var __delta
    #  delta
    ## @var __width
    #  width
    ## @var __height
    #  height
    ## @var max_text_height
    #  maximum text height
    def __init__(self):
        """! Initializer 
        @param self this object
        @return none
        """
        self.__top = 0
        return
    def set_bounds(self, lo, hi):
        """! Set Bounds 
        @param self this object
        @param lo lo
        @param hi hi
        @return none
        """
        self.__lo = lo
        self.__hi = hi
    def get_position(self, x):
        """! Get Position 
        @param self this object
        @param x x
        @return real x
        """
        real_x = (x - self.__lo ) * self.__width / (self.__hi - self.__lo)
        return real_x
    def set_top(self):
        """! Set Top 
        @param self this object
        @return none
        """
        self.__top = 1
    def set_bot(self):
        """! Set Bottom 
        @param self this object
        @return none
        """
        self.__top = 0
    def layout(self, width):
        """! Layout 
        @param self this object
        @param width width
        @return none
        """
        surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 1, 1)
        ctx = cairo.Context(surface)

        # calculate scale delta
        data_delta = self.__hi - self.__lo
        closest = 1
        while (closest*10) < data_delta:
            closest *= 10
        if (data_delta / closest) == 0:
            delta = closest
        elif(data_delta / closest) == 1:
            delta = closest / 10
        else:
            delta = closest
        start = self.__lo - (self.__lo % delta) + delta
        end = self.__hi - (self.__hi % delta)

        self.__delta = delta
        self.__width = width

        # calculate text height
        max_text_height = ctx.text_extents("ABCDEFGHIJKLMNOPQRSTUVWXYZabcedefghijklmnopqrstuvwxyz0123456789")[3]
        self.max_text_height = max_text_height
        height = max_text_height + 10
        self.__height = height

    def get_height(self):
        """! Get Height 
        @param self: this object
        @return height
        """
        return self.__height
    def draw(self, ctx):
        """! Draw 
        @param self this object
        @param ctx ctx
        @return none
        """
        delta = self.__delta
        start = self.__lo - (self.__lo % delta) + delta
        end = self.__hi - (self.__hi % delta)

        if self.__top == 1:
            s = -1
        else:
            s = 1
        # print scale points
        ctx.set_source_rgb(0, 0, 0)
        ctx.set_line_width(1.0)
        ticks = range(int(start), int(end + delta), int(delta))
        for x in ticks:
            real_x = (x - self.__lo ) * self.__width / (self.__hi - self.__lo)
            ctx.move_to(real_x, 0)
            ctx.line_to(real_x, 5*s)
            ctx.close_path()
            ctx.stroke()
            (t_y_bearing, t_width, t_height) = ctx.text_extents(str(x))[1:4]
            if self.__top:
                text_delta = t_height + t_y_bearing
            else:
                text_delta = -t_y_bearing
            ctx.move_to(real_x - t_width / 2, (5 + 5 + text_delta)*s)
            ctx.show_text(str(x))
        # draw subticks
        delta /= 10
        if delta > 0:
            start = self.__lo - (self.__lo % delta) + delta
            end = self.__hi - (self.__hi % delta)
            for x in range(int(start), int(end + delta), int(delta)):
                real_x = (x - self.__lo ) * self.__width / (self.__hi - self.__lo)
                ctx.move_to(real_x, 0)
                ctx.line_to(real_x, 3*s)
                ctx.close_path()
                ctx.stroke()


## GraphicRenderer class
class GraphicRenderer:
    ## @var __start
    #  start
    ## @var __end
    #  end
    ## @var __mid_scale
    #  mid scale
    ## @var __bot_scale
    #  bottom scale 
    ## @var __width
    #  width
    ## @var __height
    #  height
    ## @var __r_start
    #  start
    ## @var __r_end
    #  end
    ## @var __data
    #  data
    ## @var __mid_scale
    #  mid scale
    ## @var __top_legend
    #  top legend
    def __init__(self, start, end):
        """! Initializer 
        @param self this object
        @param start start
        @param end end
        @return none
        """
        self.__start = float(start)
        self.__end = float(end)
        self.__mid_scale = ScaleRenderer()
        self.__mid_scale.set_top()
        self.__bot_scale = ScaleRenderer()
        self.__bot_scale.set_bounds(start, end)
        self.__bot_scale.set_bot()
        self.__width = 1
        self.__height = 1
    def get_width(self):
        """! Get Width 
        @param self: this object
        @return width
        """
        return self.__width
    def get_height(self):
        """! Get Height 
        @param self this object
        @return height
        """
        return self.__height
    # return x, y, width, height
    def get_data_rectangle(self):
        """! Get Data Rectangle 
        @param self this object
        @return rectangle
        """
        y_start = self.__top_legend.get_height()
        x_start = self.__data.get_data_x_start()
        return(x_start, y_start, self.__width - x_start, self.__data.get_height())
    def scale_data(self, x):
        """! Get Data Rectangle 
        @param self this object
        @param x x
        @return scaled x
        """
        x_start = self.__data.get_data_x_start()
        x_scaled = x / (self.__width - x_start) * (self.__r_end - self.__r_start)
        return x_scaled
    # return x, y, width, height
    def get_selection_rectangle(self):
        """! Get Selection Rectangle 
        @param self this object
        @return rectangle
        """
        y_start = self.__top_legend.get_height() + self.__data.get_height() + self.__mid_scale.get_height() + 20
        y_height = self.__bot_scale.get_height() + 20
        x_start = self.__bot_scale.get_position(self.__r_start)
        x_end = self.__bot_scale.get_position(self.__r_end)
        return(x_start, y_start, x_end - x_start, y_height)
    def scale_selection(self, x):
        """! Scale Selection 
        @param self this object
        @param x the X
        @return scaled X
        """
        x_scaled = x / self.__width * (self.__end - self.__start)
        return x_scaled
    def set_range(self, start, end):
        """! Set Range 
        @param self this object
        @param start start
        @param end end
        @return none
        """
        s = min(start, end)
        e = max(start, end)
        start = max(self.__start, s)
        end = min(self.__end, e)
        self.__r_start = start
        self.__r_end = end
        self.__data.set_render_range(start, end)
        self.__mid_scale.set_bounds(start, end)
        self.layout(self.__width, self.__height)
    def get_range(self):
        """! Get Range 
        @param self this object
        @return range
        """
        return(self.__r_start, self.__r_end)
    def set_data(self, data):
        """! Set Date 
        @param self this object
        @param data data
        @return none
        """
        self.__data = data
    def set_top_legend(self, top_legend):
        """! Set Top Legend 
        @param self this object
        @param top_legend The legend
        @return none
        """
        self.__top_legend = top_legend
    def layout(self, width, height):
        """! Set Layout 
        @param self this object
        @param width width
        @param height height
        @return none
        """
        self.__width = width
        self.__height = height
        self.__top_legend.layout(width)
        top_legend_height = self.__top_legend.get_height()
        self.__data.layout(width)
        self.__mid_scale.layout(width - self.__data.get_data_x_start())
        self.__bot_scale.layout(width)
        return
    def __x_pixel(self, x, width):
        """! X Pixel 
        @param self this object
        @param x x
        @param width width
        @return x pixel
        """
        new_x = (x - self.__start) * width / (self.__end - self.__start)
        return new_x

    def draw(self, ctx):
        """! Draw 
        @param self this object
        @param ctx ctx
        @return none
        """
        # default background is white
        ctx.save()
        ctx.set_source_rgb(1, 1, 1)
        ctx.set_operator(cairo.OPERATOR_SOURCE)
        ctx.rectangle(0, 0, self.__width, self.__height)
        ctx.fill()

        # top legend
        ctx.save()
        self.__top_legend.draw(ctx)
        top_legend_height = self.__top_legend.get_height()
        ctx.restore()

        # separation line
        ctx.move_to(0, top_legend_height)
        ctx.line_to(self.__width, top_legend_height)
        ctx.close_path()
        ctx.set_line_width(2)
        ctx.set_source_rgb(0, 0, 0)
        ctx.stroke()

        # data
        ctx.save()
        ctx.translate(0, 
                       top_legend_height)
        self.__data.draw(ctx)
        ctx.restore()

        # scale below data
        ctx.save()
        ctx.translate(self.__data.get_data_x_start(), 
                       top_legend_height + self.__data.get_height() + self.__mid_scale.get_height())
        self.__mid_scale.draw(ctx)
        ctx.restore()

        height_used = top_legend_height + self.__data.get_height() + self.__mid_scale.get_height()

        # separation between scale and left pane
        ctx.move_to(self.__data.get_data_x_start(), height_used)
        ctx.rel_line_to(0, -self.__mid_scale.get_height())
        ctx.close_path()
        ctx.set_source_rgb(0, 0, 0)
        ctx.set_line_width(2)
        ctx.stroke()

        # separation below scale
        ctx.move_to(0, height_used)
        ctx.line_to(self.__width, height_used)
        ctx.close_path()
        ctx.set_line_width(2)
        ctx.set_source_rgb(0, 0, 0)
        ctx.stroke()

        select_start = self.__bot_scale.get_position(self.__r_start)
        select_end = self.__bot_scale.get_position(self.__r_end)

        # left connection between top scale and bottom scale
        ctx.move_to(0, height_used);
        ctx.line_to(self.__data.get_data_x_start(), height_used)
        ctx.line_to(select_start, height_used + 20)
        ctx.line_to(0, height_used + 20)
        ctx.line_to(0, height_used)
        ctx.set_source_rgb(0, 0, 0)
        ctx.set_line_width(1)
        ctx.stroke_preserve()
        ctx.set_source_rgb(0.9, 0.9, 0.9)
        ctx.fill()

        # right connection between top scale and bottom scale
        ctx.move_to(self.__width, height_used)
        ctx.line_to(self.__width, height_used + 20)
        ctx.line_to(select_end, height_used + 20)
        ctx.line_to(self.__width, height_used)
        ctx.set_source_rgb(0, 0, 0)
        ctx.set_line_width(1)
        ctx.stroke_preserve()
        ctx.set_source_rgb(0.9, 0.9, 0.9)
        ctx.fill()

        height_used += 20

        # unused area background
        unused_start = self.__bot_scale.get_position(self.__r_start)
        unused_end = self.__bot_scale.get_position(self.__r_end)
        unused_height = self.__bot_scale.get_height() + 20
        ctx.rectangle(0, height_used, 
                       unused_start, 
                       unused_height)
        ctx.rectangle(unused_end, 
                       height_used, 
                       self.__width - unused_end, 
                       unused_height)
        ctx.set_source_rgb(0.9, 0.9, 0.9)
        ctx.fill()

        # border line around bottom scale
        ctx.move_to(unused_end, height_used)
        ctx.line_to(self.__width, height_used)
        ctx.line_to(self.__width, height_used + unused_height)
        ctx.line_to(0, height_used + unused_height)
        ctx.line_to(0, height_used)
        ctx.line_to(unused_start, height_used)
        ctx.close_path()
        ctx.set_line_width(2)
        ctx.set_source_rgb(0, 0, 0)
        ctx.stroke()
        ctx.move_to(unused_start, height_used)
        ctx.line_to(unused_end, height_used)
        ctx.close_path()
        ctx.set_line_width(1)
        ctx.set_source_rgb(0.9, 0.9, 0.9)
        ctx.stroke()

        # unused area dot borders
        ctx.save()
        ctx.move_to(max(unused_start, 2), height_used)
        ctx.rel_line_to(0, unused_height)
        ctx.move_to(min(unused_end, self.__width - 2), height_used)
        ctx.rel_line_to(0, unused_height)
        ctx.set_dash([5], 0)
        ctx.set_source_rgb(0, 0, 0)
        ctx.set_line_width(1)
        ctx.stroke()
        ctx.restore()

        # bottom scale
        ctx.save()
        ctx.translate(0, height_used)
        self.__bot_scale.draw(ctx)
        ctx.restore()

## GtkGraphicRenderer class
class GtkGraphicRenderer(gtk.DrawingArea):
    ## @var __data
    #  data
    ## @var __moving_left
    #  moving left
    ## @var __moving_right
    #  moving right
    ## @var __moving_both
    #  moving both
    ## @var __moving_top
    #  moving top
    ## @var __force_full_redraw
    #  full redraw
    ## @var __moving_left_cur
    #  moving left cur
    ## @var __moving_right_cur
    #  moving right cur
    ## @var __moving_both_start
    #  moving both start
    ## @var __moving_both_cur
    #  moving both cur
    ## @var __moving_top_cur
    #  moving top cur
    ## @var __moving_top_start
    #  moving top start
    ## @var __width
    #  width
    ## @var __height
    #  height
    ## @var __buffer_surface
    #  buffer surface 
    def __init__(self, data):
        """! Initializer
        @param self this object
        @param data data
        @return none
        """
        super(GtkGraphicRenderer, self).__init__()
        self.__data = data
        self.__moving_left = False
        self.__moving_right = False
        self.__moving_both = False
        self.__moving_top = False
        self.__force_full_redraw = True
        self.add_events(gtk.gdk.POINTER_MOTION_MASK)
        self.add_events(gtk.gdk.BUTTON_PRESS_MASK)
        self.add_events(gtk.gdk.BUTTON_RELEASE_MASK)
        self.connect("expose_event", self.expose)
        self.connect('size-allocate', self.size_allocate)
        self.connect('motion-notify-event', self.motion_notify)
        self.connect('button-press-event', self.button_press)
        self.connect('button-release-event', self.button_release)
    def set_smaller_zoom(self):
        """! Set Smaller Zoom
        @param self this object
        @return none
        """
        (start, end) = self.__data.get_range()
        self.__data.set_range(start, start + (end - start)*2)
        self.__force_full_redraw = True
        self.queue_draw()
    def set_bigger_zoom(self):
        """! Set Bigger Zoom
        @param self this object
        @return none
        """
        (start, end) = self.__data.get_range()
        self.__data.set_range(start, start + (end - start) / 2)
        self.__force_full_redraw = True
        self.queue_draw()
    def output_png(self, filename):
        """! Output PNG
        @param self this object
        @param filename file name
        @return none
        """
        surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 
                                     self.__data.get_width(), 
                                     self.__data.get_height())
        ctx = cairo.Context(self.__buffer_surface)
        self.__data.draw(ctx)
        surface.write_to_png(filename)
    def button_press(self, widget, event):
        """! Button Press
        @param self this object
        @param widget widget
        @param event event
        @return true if button has been pressed otherwise false
        """
        (x, y, width, height) = self.__data.get_selection_rectangle()
        (d_x, d_y, d_width, d_height) = self.__data.get_data_rectangle()
        if event.y > y and event.y < y + height:
            if abs(event.x - x) < 5:
                self.__moving_left = True
                return True
            if abs(event.x - (x + width)) < 5:
                self.__moving_right = True
                return True
            if event.x > x and event.x < x + width:
                self.__moving_both = True
                self.__moving_both_start = event.x
                self.__moving_both_cur = event.x
                return True
        if event.y > d_y and event.y < (d_y + d_height):
            if event.x > d_x and event.x < (d_x + d_width):
                self.__moving_top = True
                self.__moving_top_start = event.x
                self.__moving_top_cur = event.x
                return True
        return False
    def button_release(self, widget, event):
        """! Button Release
        @param self this object
        @param widget widget
        @param event event
        @return true if button was released otherwise false
        """
        if self.__moving_left:
            self.__moving_left = False
            left = self.__data.scale_selection(self.__moving_left_cur)
            right = self.__data.get_range()[1]
            self.__data.set_range(left, right)
            self.__force_full_redraw = True
            self.queue_draw()
            return True
        if self.__moving_right:
            self.__moving_right = False
            right = self.__data.scale_selection(self.__moving_right_cur)
            left = self.__data.get_range()[0]
            self.__data.set_range(left, right)
            self.__force_full_redraw = True
            self.queue_draw()
            return True
        if self.__moving_both:
            self.__moving_both = False
            delta = self.__data.scale_selection(self.__moving_both_cur - self.__moving_both_start)
            (left, right) = self.__data.get_range()
            self.__data.set_range(left + delta, right + delta)
            self.__force_full_redraw = True
            self.queue_draw()
            return True
        if self.__moving_top:
            self.__moving_top = False
        return False
    def motion_notify(self, widget, event):
        """! Motion Notify
        @param self this object
        @param widget widget
        @param event event
        @return true if moving otherwise false
        """
        (x, y, width, height) = self.__data.get_selection_rectangle()
        if self.__moving_left:
            if event.x <= 0:
                self.__moving_left_cur = 0
            elif event.x >= x + width:
                self.__moving_left_cur = x + width
            else:
                self.__moving_left_cur = event.x
            self.queue_draw_area(0, int(y), int(self.__width), int(height))
            return True
        if self.__moving_right:
            if event.x >= self.__width:
                self.__moving_right = self.__width
            elif event.x < x:
                self.__moving_right_cur = x
            else:
                self.__moving_right_cur = event.x
            self.queue_draw_area(0, int(y), int(self.__width), int(height))
            return True
        if self.__moving_both:
            cur_e = self.__width - (x + width - self.__moving_both_start)
            cur_s = (self.__moving_both_start - x)
            if event.x < cur_s:
                self.__moving_both_cur = cur_s
            elif event.x > cur_e:
                self.__moving_both_cur = cur_e
            else:
                self.__moving_both_cur = event.x
            self.queue_draw_area(0, int(y), int(self.__width), int(height))
            return True
        if self.__moving_top:
            self.__moving_top_cur = event.x
            delta = self.__data.scale_data(self.__moving_top_start - self.__moving_top_cur)
            (left, right) = self.__data.get_range()
            self.__data.set_range(left + delta, right + delta)
            self.__force_full_redraw = True
            self.__moving_top_start = event.x
            self.queue_draw()
            return True
        (d_x, d_y, d_width, d_height) = self.__data.get_data_rectangle()
        if event.y > y and event.y < y + height:
            if abs(event.x - x) < 5 or abs(event.x - (x + width)) < 5:
                widget.window.set_cursor(gtk.gdk.Cursor(gtk.gdk.SB_H_DOUBLE_ARROW))
                return True
            if event.x > x and event.x < x + width:
                widget.window.set_cursor(gtk.gdk.Cursor(gtk.gdk.FLEUR))
                return True
        if event.y > d_y and event.y < (d_y + d_height):
            if event.x > d_x and event.x < (d_x + d_width):
                widget.window.set_cursor(gtk.gdk.Cursor(gtk.gdk.FLEUR))
                return True
        widget.window.set_cursor(None)
        return False
    def size_allocate(self, widget, allocation):
        """! Size Allocate
        @param self this object
        @param widget widget
        @param allocation allocation
        @return none
        """
        self.__width = allocation.width
        self.__height = allocation.height
        self.__data.layout(allocation.width, allocation.height)
        self.__force_full_redraw = True
        self.queue_draw()
    def expose(self, widget, event):
        """! Expose
        @param self this object
        @param widget widget
        @param event event
        @return false
        """
        if self.__force_full_redraw:
            self.__buffer_surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 
                                                       self.__data.get_width(), 
                                                       self.__data.get_height())
            ctx = cairo.Context(self.__buffer_surface)
            self.__data.draw(ctx)
            self.__force_full_redraw = False
        ctx = widget.window.cairo_create()
        ctx.rectangle(event.area.x, event.area.y, 
                      event.area.width, event.area.height)
        ctx.clip()
        ctx.set_source_surface(self.__buffer_surface)
        ctx.paint()
        (x, y, width, height) = self.__data.get_selection_rectangle()
        if self.__moving_left:
            ctx.move_to(max(self.__moving_left_cur, 2), y)
            ctx.rel_line_to(0, height)
            ctx.close_path()
            ctx.set_line_width(1)
            ctx.set_source_rgb(0, 0, 0)
            ctx.stroke()
        if self.__moving_right:
            ctx.move_to(min(self.__moving_right_cur, self.__width - 2), y)
            ctx.rel_line_to(0, height)
            ctx.close_path()
            ctx.set_line_width(1)
            ctx.set_source_rgb(0, 0, 0)
            ctx.stroke()
        if self.__moving_both:
            delta_x = self.__moving_both_cur - self.__moving_both_start
            left_x = x + delta_x
            ctx.move_to(x + delta_x, y)
            ctx.rel_line_to(0, height)
            ctx.close_path()
            ctx.move_to(x + width + delta_x, y)
            ctx.rel_line_to(0, height)
            ctx.close_path()
            ctx.set_source_rgb(0, 0, 0)
            ctx.set_line_width(1)
            ctx.stroke()
        return False

## MainWindow class
class MainWindow:
    ## @var __window
    #  window
    ## @var __render
    #  render
    ## @var __dialog
    #  dialog
    def __init__(self):
        """! Initializer
        @param self this object
        @return none
        """
        return
    def run(self, graphic):
        """! Run function
        @param self this object
        @param graphic graphic
        @return none
        """
        window = gtk.Window()
        self.__window = window
        window.set_default_size(200, 200)
        vbox = gtk.VBox()
        window.add(vbox)
        render = GtkGraphicRenderer(graphic)
        self.__render = render
        vbox.pack_end(render, True, True, 0)
        hbox = gtk.HBox()
        vbox.pack_start(hbox, False, False, 0)
        smaller_zoom = gtk.Button("Zoom Out")
        smaller_zoom.connect("clicked", self.__set_smaller_cb)
        hbox.pack_start(smaller_zoom)
        bigger_zoom = gtk.Button("Zoom In")
        bigger_zoom.connect("clicked", self.__set_bigger_cb)
        hbox.pack_start(bigger_zoom)
        output_png = gtk.Button("Output Png")
        output_png.connect("clicked", self.__output_png_cb)
        hbox.pack_start(output_png)
        window.connect('destroy', gtk.main_quit)
        window.show_all()
        #gtk.bindings_activate(gtk.main_quit, 'q', 0)
        gtk.main()
    def __set_smaller_cb(self, widget):
        """! Set Smaller Callback
        @param self this object
        @param widget widget
        @return none
        """
        self.__render.set_smaller_zoom()
    def __set_bigger_cb(self, widget):
        """! Set Bigger Callback
        @param self this object
        @param widget widget
        @return none
        """
        self.__render.set_bigger_zoom()
    def __output_png_cb(self, widget):
        """! Output PNG Callback
        @param self this object
        @param widget widget
        @return none
        """
        dialog = gtk.FileChooserDialog("Output Png", self.__window, 
                                       gtk.FILE_CHOOSER_ACTION_SAVE, ("Save", 1))
        self.__dialog = dialog
        dialog.set_default_response(1)
        dialog.connect("response", self.__dialog_response_cb)
        dialog.show()
        return
    def __dialog_response_cb(self, widget, response):
        """! Dialog Response Callback
        @param self this object
        @param widget widget
        @param response response
        @return none
        """
        if response == 1:
            filename = self.__dialog.get_filename()
            self.__render.output_png(filename)
            widget.hide()
        return


## read_data function
def read_data(filename):
    timelines = Timelines()
    colors = Colors()
    fh = open(filename)
    m1 = re.compile('range ([^ ]+) ([^ ]+) ([^ ]+) ([0-9]+) ([0-9]+)')
    m2 = re.compile('event-str ([^ ]+) ([^ ]+) ([^ ]+) ([0-9]+)')
    m3 = re.compile('event-int ([^ ]+) ([^ ]+) ([0-9]+) ([0-9]+)')
    m4 = re.compile('color ([^ ]+) #([a-fA-F0-9]{2,2})([a-fA-F0-9]{2,2})([a-fA-F0-9]{2,2})')
    for line in fh.readlines():
        m = m1.match(line)
        if m:
            line_name = m.group(1)
            timeline = timelines.get(m.group(1))
            rang = timeline.get_range(m.group(2))
            data_range = DataRange()
            data_range.value = m.group(3)
            data_range.start = int(m.group(4))
            data_range.end = int(m.group(5))
            rang.add_range(data_range)
            continue
        m = m2.match(line)
        if m:
            line_name = m.group(1)
            timeline = timelines.get(m.group(1))
            ev = timeline.get_event_str(m.group(2))
            event = EventString()
            event.value = m.group(3)
            event.at = int(m.group(4))
            ev.add_event(event)
            continue
        m = m3.match(line)
        if m:
            line_name = m.group(1)
            timeline = timelines.get(m.group(1))
            ev = timeline.get_event_int(m.group(2))
            event = EventInt()
            event.value = int(m.group(3))
            event.at = int(m.group(4))
            ev.add_event(event)
            continue

        m = m4.match(line)
        if m:
            r = int(m.group(2), 16)
            g = int(m.group(3), 16)
            b = int(m.group(4), 16)
            color = Color(r / 255, g / 255, b / 255)
            colors.add(m.group(1), color)
            continue
    timelines.sort()
    return (colors, timelines)



def main():
    (colors, timelines) = read_data(sys.argv[1])
    (lower_bound, upper_bound) = timelines.get_bounds()
    graphic = GraphicRenderer(lower_bound, upper_bound)
    top_legend = TopLegendRenderer()
    range_values = timelines.get_all_range_values()
    range_colors = []
    for range_value in range_values:
        range_colors.append(colors.lookup(range_value))
    top_legend.set_legends(range_values, 
                           range_colors)
    graphic.set_top_legend(top_legend)
    data = TimelinesRenderer()
    data.set_timelines(timelines, colors)
    graphic.set_data(data)

    # default range
    range_mid = (upper_bound - lower_bound) / 2
    range_width = (upper_bound - lower_bound) / 10
    range_lo = range_mid - range_width / 2
    range_hi = range_mid + range_width / 2
    graphic.set_range(range_lo, range_hi)

    main_window = MainWindow()
    main_window.run(graphic)


main()

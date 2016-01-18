import png
#from PIL import Image
import Image, ImageDraw, ImageFont
import math
import numpy as np
from operator import sub
import sys
from sys import argv
from collections import namedtuple

#Data structures
DockData = namedtuple("DockData", "terminal num_doors islands scales bays")
TruckData = namedtuple("TrucksData", "dest handling_units weight head_count tail_count doors destinations")
Scales = namedtuple("Scales", "bay location")
Islands = namedtuple("Islands", "bay location orientation")


#Data retreaval code //////////////////////////////////////////////////////////////////////////////
def get_string():
	string = raw_input("");
	return string;

def get_islands():
	islands = []
	bay = get_string()
	while(bay != "END"):
		loc = get_string()
		orient = get_string()
		island = Islands(bay, loc, orient)
		islands.append(island)
		bay = get_string()
	return islands

def get_scales():
	scales = []
	bay = get_string()
	while(bay != "END"):
		loc = get_string()
		scale = Scales(bay, loc)
		scales.append(scale)
		bay = get_string()
	return scales

def get_char_array():
	arr = []
	label = get_string()
	while(label != "END"):
		arr.append(label)
		label = get_string()
	return arr

def get_dock_info():
	term = get_string()
	num_doors = get_string()
	islands = get_islands()
	scales = get_scales()
	bays = get_char_array()

	dock_info = DockData(term, num_doors, islands, scales, bays)
	return dock_info
	
def get_trucks_info():
	trucks = []
	dest = get_string()
	while(dest != "FINISHED"):
		truck = get_truck_info(dest)
		dest = get_string()
		trucks.append(truck)
	return trucks
	
def get_truck_info(dest):
	handling_units = get_string()
	weight = get_string()
	head_count = get_string()
	tail_count = get_string()
	doors = get_char_array()
	destinations = get_char_array()
	
	truck = TruckData(dest, handling_units, weight, head_count, tail_count, doors, destinations);
	return truck
#End data retrieval code //////////////////////////////////////////////////////////////////////////


#Misc drawing code////////////////////////////////////////////////////////////////////////////////
def draw_square(x, y, fx, fy, w):
	draw.line((x,y,x ,fy), width = w, fill = (0,0,0));
	draw.line((x, y, fx,y ), width = w, fill = (0,0,0));
	draw.line((fx,fy , x, fy), width = w, fill = (0,0,0));
	draw.line((fx,fy,fx,y ), width = w, fill = (0,0,0));	
	
def display_location(x, y):
	l = 10
	x1 = x - l
	x2 = x + l
	y1 = y - l
	y2 = y + l
	draw.line((x1,y1,x2,y2), width = 1, fill = (0,0,0));
	draw.line((x2,y1,x1,y2), width = 1, fill = (0,0,0));
#End misc drqwing code//////////////////////////////////////////////////////////////////////////
	

#Draw Load information code///////////////////////////////////////////////////////////////////
def draw_load_info(draw, dock_info, trucks_info, width, b):
	s = 1.5		#scale of drawn items
	size_bay_number_DT = int(s*25)
	spacing = s*85
	xstart = b + s*40		#x and y are going to be the quardanits of itmes to be drawn
	title_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", b)
	title = dock_info.terminal + " Load Plan"
	draw.text((width/2 - 3*b*s, b), title, (0,0,0), font = title_font);
	ystart = b*2
	x = xstart
	y = ystart
	coordinates = []
	end = 0
	loc = 0
	for i in range(0, len(trucks_info)):
		y = draw_door_number(x, y, trucks_info[i], s)
		y = draw_truck_destination(x, y, trucks_info[i].dest, s)
		y = draw_hu_weight(x,y,trucks_info[i], s)
		y = draw_freight_destinations(x, y, trucks_info[i], s)

		y = find_end(x, ystart, y, s)
		coordinat, end, loc = find_coordinats(x, y, ystart, spacing, coordinates, width, end, s, loc)
		x = coordinat[0]
		y = coordinat[1]
		ystart = y
		
	return find_highest_y(coordinates)
		
def find_coordinats(x, y, ystart, spacing, coordinates, width, end, s, loc):
	xnext = x + spacing
	if(end):
		coordinates[loc] = (x,y)
		loc = find_lowest_point((coordinates))
		return coordinates[loc], end, loc
	else:
		if(xnext + spacing > width):
			coordinates.append((x,y))
			loc = find_lowest_point((coordinates))
			return coordinates[loc], 1, loc
		else:
			coordinates.append((x,y))
			return (xnext, ystart), end, loc
			
		
def find_lowest_point(xy):
	maximum = 0
	for i in range (1, len(xy)):
		if(xy[maximum][1] > xy[i][1] and xy[i][1] != 0):
			maximum = i
	return maximum
	
	
def find_highest_y(xy):
	maximum = 0
	for i in range (1, len(xy)):
		if(xy[maximum][1] < xy[i][1] and xy[i][1] != 0):
			maximum = i
	return xy[maximum][1]
	
	
def draw_freight_destinations(x, y, truck, s):
	size_dts = int(s*15)
	dts_headTail_font = ImageFont.truetype("../TextFormats/FreeMonoBoldOblique.ttf", size_dts)
	dts_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", size_dts)
	tiny_size = int(s*10)
	tiny_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", tiny_size)
	dests = truck.destinations
	head = int(truck.head_count)
	tail = int(truck.tail_count)
	if(len(dests) > 1 or truck.dest != dests[0]):
		for i in range(0, len(dests)):
			fnt = dts_font
			if(i < head or i > len(dests) - tail - 1):
				if(i == head - 1):
					draw.text((x - size_dts - s*8, y + s * 5), "H", (0,0,0), font = tiny_font)
				if(len(dests) - i == tail):
					draw.text((x + size_dts, y - s * .5), "T", (0,0,0), font = tiny_font)
				fnt = dts_headTail_font

			draw.text((x - size_dts, y), dests[i], (0,0,0), font = fnt)
			y += size_dts
	return y
	
		
def find_end(x, ystart, y, s):
	unit = s*67
	end = unit
	spacing = s*2;
	size = y - ystart
	while(end < size):
		end += unit
		spacing += s
	ret = end + ystart
	draw_square(x-s*40, ystart, x+s*40, ret, 1)
	return ret + spacing
	
		
def draw_truck_destination(x, y, dest, s):
	dest_number = int(s*25)
	dest_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", dest_number)
	draw.text((x - s*dest_number*.65, y), dest, (0,0,0), font = dest_font)
	return y + dest_number
	
		
def draw_hu_weight(x, y, truck, s):
	size_weight_hu = int(s*15)
	weight_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", size_weight_hu)
	string = truck.handling_units + ":" + truck.weight
	start = int(x - len(string)*s*4.5)
	draw.text((start, y), string, (0,0,0), font = weight_font);
	return y + size_weight_hu
	
def draw_door_number(x, y, truck_info, s):
	size_number = int(s*25)
	number_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", size_number)
	doors = door_string(truck_info)
	odd = 0
	if(len(doors) %2 == 1):
		odd = 1
	count = 0;
	for i in range (0, len(doors), 2):
		start = int(x - len(doors[i])*s*7.5)
		draw.text((start, y), doors[i], (0,0,0), font = number_font)
		y += size_number
		count += 1
	
	return y
		
	
def door_string(truck_info):
	strings = []
	doors = truck_info.doors
	for i in range(0, len(doors)):
		string = doors[i]
		if(i + 1 < len(doors)):
			string = string + "/" + doors[i + 1]
		strings.append(string)
	return strings
	
#End draw load information code///////////////////////////////////////////////////////////////


#Draw dock layout code//////////////////////////////////////////////////////////////////////////
def draw_square(x, y, fx, fy, w):
	draw.line((x,y,x ,fy), width = w, fill = (0,0,0));
	draw.line((x, y, fx,y ), width = w, fill = (0,0,0));
	draw.line((fx,fy , x, fy), width = w, fill = (0,0,0));
	draw.line((fx,fy,fx,y ), width = w, fill = (0,0,0));	
	
	
def outline(s, dl, h, sx, sy):
	w = 1
	x = sx
	y = sy
	fx = x + dl - 1 + s
	fy = sy + s*h - 1 - s
	draw_square(x, y, fx, fy, w);

def doors( h, d, sx, sy, s):
	w = 1
	x = sx + s
	y = sy 
	
	for i in range(0, d/2 + 1):
		x1 = x - .5*s
		y1 = y
		x2 =  x - .5*s
		y2 = y + 6
		draw.line((x1,y1,x2 ,y2), width = s-2, fill = (0,0,0));
		y3 = y1 + s*h - 1 - 1.5*s
		y4 = y3 + 6
		draw.line((x1,y3,x2,y4), width = s- 2, fill = (0,0,0));
		x += 5*s
	


	
def full_bay(s, sx, sy, d, h):
	w = 1
	x = sx + 7*s
	for i in range(0, int(math.ceil(d/4.0) )- 1):
		x1 = x + s*1.5
		y1 = sy + 4*s
		x2 = x + s*5.5
		y2 = sy + (h - 5)*s
		ydiff = y1 + (y2 - y1)/2
		draw_square(x1, y1, x2, y2, w)
		if(not structure_exist(i + 1)):
			draw.line((x1,ydiff,x2,ydiff ), width = w, fill = (0,0,0));
		x += 10*s
		
def structure_exist(bay):
	scales = dock_info.scales
	for i in range (0, len(scales)):
		if(int(scales[i].bay) == bay and scales[i].location == "Middle"):
			return 1
		
	islands = dock_info.islands
	for i in range(0, len(islands)):
		if(int(islands[i].bay) == bay and islands[i].location == "Middle"):
			return 1
	return 0
		
def half_bay(s, dl, sx, sy, h):
	w = 1
	x1 = sx + s
	y1 = sy + 4*s
	x2 = x1 + 1.5*s
	y2 = sy + h*s - 5*s
	ydiff = y1 + (y2 - y1)/2
	draw_square(x1, y1, x2, y2, w)
	draw.line((x1,ydiff,x2,ydiff ), width = w, fill = (0,0,0));
	x3 = x1 + dl - 1
	x4 = x3 - 1.5*s 
	draw_square(x3, y1, x4, y2, w)
	draw.line((x3,ydiff,x4,ydiff ), width = w, fill = (0,0,0));
	return
		
		
def set_numbers(d, s, sx, sy, h):
	font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 25)
	x = sx + s
	yt = sy 
	yb = yt + h*s - 3.75*s
	for i in range (1, d+1):
		st = str(i)
		if( len(st) == 1):
			z = x + .75*s
		else:
			z = x
		if(i % 2 == 1):
			draw.text((z,yb ), st, (0,0,0), font=font)
		else:
			draw.text((z,yt ), st, (0,0,0), font=font)
			x += 5*s
			
def set_bay_numbers(sx, sy, s, h):
	font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 25)
	small_font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 14)
	bays = dock_info.bays
	for i in range(0, len(bays)):
		off = len(bays[i])*s - s*.2
		if(i % 2 == 1):
			xstart = 5*s*(i - 1) + sx + 10.5*s
			ystart = sy + 4*s
			draw.text((xstart - off, ystart), bays[i], (0,0,0), font = font);
			#draw.text((xstart - s*1.7, ystart + 20), "Head", (0,0,0), font = small_font)
		else:
			xstart = 5*s*i - 1 + sx + 10.5*s
			ystart = sy + 4*s + 9*h*s/20
			draw.text((xstart - off, ystart), bays[i], (0,0,0), font = font);
			#if "Tail" in bays[i]:
			#draw.text((xstart - s*1.7, ystart + 20), "Tail", (0,0,0), font = small_font)
				

def circle_doors(h, sx, sy, s):
	w = 1
	centerx = sx + .55*s 
	centery = sy + 1.5*s
	r = 2.45*s
	for i in range (0, len(trucks_info)):
		truck = trucks_info[i]
		for j in range(0, len(truck.doors)):
			ds = int(truck.doors[j])
			if(ds < int(dock_info.num_doors) + 1 and ds > 0):
				if(ds % 2 == 0):
					shiftx = s*5*int(ds/2)  - 2.4*s
					tl = (int(shiftx + centerx - r), int(centery - r), int (shiftx + centerx + r), int(centery + r))
					draw.arc(tl, 0, 360, fill = (0,0,0))
				else:
					shiftx = s*5*ds/2 
					shifty = s*(h - 3.5)
					a = (int(shiftx + centerx - r), int(shifty + centery - r), int (shiftx + centerx + r), int(shifty + centery + r))
					draw.arc(a, 0, 360, fill = (0,0,0))
			
			
			
def draw_island(stx, sty, h, s):	
	w = 1
	draw = ImageDraw.Draw(image)
	for i in range (0, len(dock_info.islands)):
		bay = int(dock_info.islands[i].bay)
		location = dock_info.islands[i].location
		orientation = dock_info.islands[i].orientation
		d = 1
		ly = s*((h-8)/3)
		lx = (bay - 1) *10*s
		sx = stx +8.5*s + lx
		sy = sty + 4*s + ly	
		if "M" in location:
			sy = sty + 4*s + ly	
		if "B" in location:
			sy += ly
		elif "T" in location:
			sy -= ly
		if "U" in orientation:
			d = -1
			sy += ly
			sx += 4*s
		#if(location == "Top" and orientation == "Down"):
			#sy -= ly	
		#if(location == "Bottom" and orientation == "Up"):
			#sy += ly
		
		uol = (sx, sy)
		uor = (sx + d*4*s, sy)
		lol = (sx, sy+d*ly-d*s)
		lor = (sx +d*4*s,sy + d*ly-d*s)
		draw_square(uol[0], uol[1], lor[0], lor[1], w)

		uil = tuple(map(sub, uol, (d*-.5*s,d*- .5*s)))
		uir = tuple(map(sub, uor, (d*.5*s, d*-.5*s)))
		lil = tuple(map(sub,lol, (d*-.5*s, d*.5*s)))
		lir = tuple(map(sub, lor, (d*.5*s, d*.5*s)))

		draw.line((uil[0],uil[1],uir[0] ,uir[1]), width = w, fill = (0,0,0));
		draw.line((uil[0],uil[1],lil[0],lil[1] ), width = w, fill = (0,0,0));
		draw.line((uir[0],uir[1],lir[0],lir[1]), width = w, fill = (0,0,0));
	
		ro = tuple(map(sub, lir, (d*s, 0)))
		lo = tuple(map(sub, lil, (d*-s, 0)))
		tsl = tuple(map(sub, lo, (0, d*-5*s/6)))
		msl = tuple(map(sub, lo, (0,d*- 7*s/6)))
		bsl = tuple(map(sub, lo, (0, d*-9*s/6)))
		tsr = tuple(map(sub, ro, (0, d*-5*s/6)))
		msr = tuple(map(sub, ro, (0, d*-7*s/6)))
		bsr = tuple(map(sub, ro, (0, d*-9*s/6)))
	
		draw.line((lo[0],lo[1],lil[0],lil[1] ), width = w, fill = (0,0,0));
		draw.line((ro[0],ro[1],lir[0],lir[1]), width = w, fill = (0,0,0));
	
		draw.line((ro[0],ro[1],bsr[0] ,bsr[1]), width = w, fill = (0,0,0));
		draw.line((lo[0],lo[1],bsl[0],bsl[1] ), width = w, fill = (0,0,0));

		draw.line((msl[0],msl[1],msr[0] ,msr[1]), width = w, fill = (0,0,0));
		draw.line((bsr[0],bsr[1],bsl[0],bsl[1] ), width = w, fill = (0,0,0));
		draw.line((tsr[0],tsr[1],tsl[0],tsl[1] ), width = w, fill = (0,0,0));
		
	
def draw_scale(dock_info, h, stx, sty, s):
	spacing = 4*s
	unit = (h-9)*s/3
	scales = dock_info.scales
	w = int(s*3)
	for i in range(0, len(scales)):
		xstart = 10*s*(int(scales[i].bay) - 1) + stx + 10.5*s
		if(scales[i].location == "Top"):
			offset = 0
		if(scales[i].location == "Bottom"):
			offset = 2*unit
		if(scales[i].location == "Middle"):
			offset = unit
		ystart = sty + spacing + offset
		draw.line((xstart,ystart + .5*s, xstart, ystart + unit - .5*s), width = w, fill = (0,0,0));	
	
	
	
def draw_dock(width, length, draw, trucks_info, dock_info, y, b):
	s = 10						#scale
	h = 24

	terminal = dock_info.terminal
	display = 1
	arg = dock_info.bays
	number_doors = int(dock_info.num_doors)
	dl = s*(number_doors*5/2 +1)   										#dock width
	image = Image.open("../Images/load_layout_plan.png");

	bx = b
	by = y + b/4

	draw = ImageDraw.Draw(image)
	font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 25)


	outline(s, dl, h, bx, by)
	doors(h, number_doors, bx,by, s)
	full_bay(s, bx, by, number_doors, h)
	half_bay(s, dl, bx, by, h)
	set_numbers(number_doors, s, bx, by, h)
	set_bay_numbers(bx, by, s, h)
	circle_doors(h, bx, by, s)
	draw_island(bx, by, h, s)
	draw_scale(dock_info, h, bx, by, s)


	if(0):
		original = Image.open("../Images/load_plan.png")
		width, height = original.size
		margin = 4*s
		left = bx - margin
		top = by - margin
		right = width
		bottom = height
		cropped = original.crop((int(left), int(top), int(right), int(bottom)))
		cropped.show()
		
		
#End draw dock layout code/////////////////////////////////////////////////////////////////////


#Main code//////////////////////////////////////////////////////////////////////////////////////////
#sys.stdin = open("test.txt")

dock_info = get_dock_info()
trucks_info = get_trucks_info()

b = 40		#Boarder of image

width = int(1800)
length = int(1200)
image = Image.new("RGBA", (width, length), (255,255,255))
draw = ImageDraw.Draw(image)

y = draw_load_info(draw, dock_info, trucks_info, width, b)
draw_dock(width, length, draw, trucks_info, dock_info, y, b)


f = open('../Images/load_plan.png', 'wb')
image.save(f, "PNG")










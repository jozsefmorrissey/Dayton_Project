import png
from PIL import Image
import Image, ImageDraw, ImageFont
import math
import numpy as np
from operator import sub
import sys
from sys import argv
import subprocess
import matplotlib.pyplot as plt


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

def doors( h, d, sx, sy):
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
		draw.line((x1,ydiff,x2,ydiff ), width = w, fill = (0,0,0));
		x += 10*s
		
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
			
def set_bay_numbers(arg, d, sx, sy):
	x = sx + 8.5*s
	yt = sy + 4*s
	yb = yt + (h - 14)*s
	limit = int((d-4)/2) 
	#if(limit % 2 == 0):
		#limit += 1
	for i in range (0,  limit):
		#error(i)
		st = str(i)
		if( len(st) == 1):
			z = x + .75*s
		else:
			z = x
		if(arg[i] != "O"):
			if(i % 2 == 0):
				draw.text((z,yb ), arg[i], (0,0,0), font=font)
				f = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 12)
				draw.text((z,yb + 2.5*s ), "Tail", (0,0,0), font=f)
				
			else:
				draw.text((z,yt ), arg[i], (0,0,0), font=font)
				f = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 12)
				draw.text((z,yt + 2.5*s ), "Head", (0,0,0), font=f)
				x += 10*s


def circle_doors(ds, h, sx, sy, s):
	w = 1
	centerx = sx + .55*s 
	centery = sy + 1.5*s
	r = 2.45*s
	for i in range (0, len(ds)):
		if(ds[i] % 2 == 0):
			shiftx = s*5*int(ds[i]/2)  - 2.4*s
			tl = (int(shiftx + centerx - r), int(centery - r), int (shiftx + centerx + r), int(centery + r))
			draw.arc(tl, 0, 360, fill = (0,0,0))
		else:
			shiftx = s*5*ds[i]/2 
			shifty = s*(h - 3.5)
			a = (int(shiftx + centerx - r), int(shifty + centery - r), int (shiftx + centerx + r), int(shifty + centery + r))
			draw.arc(a, 0, 360, fill = (0,0,0))
			
			
			
def draw_island(info, image, stx, sty, h, s):
	w = 1
	draw = ImageDraw.Draw(image)
	for i in range (0, len(info)):
		bay = info[i][0]
		location = info[i][1]
		orientation = info[i][2]
		d = 1
		ly = s*((h-8)/3)
		lx = (bay - 1) *10*s
		sx = stx +8.5*s + lx
		sy = sty + 4*s + ly
		if "M" in location:	
			erase_center_line(sx, ly, sy)
		if "B" in location:
			sy += ly
		elif "T" in location:
			sy -= ly
		if "U" in orientation:
			d = -1
			sy += ly
			sx += 4*s
		

		
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
		

def erase_center_line(sx, ly, sy):
	ex1 = sx
	ex2 = sx + 4*s
	ey = sy + ly/2
	draw.line((ex1,ey,ex2,ey ), width = 3, fill = (255,255,255));
	
def draw_scale(info, h, stx, sty, s):
	for i in range(0, len(info)):
		bay = info[i][0]
		location = info[i][1]
		ly = s*((h-8)/3)
		lx = (bay - 1) *10*s
		xfin = (lx - stx)/2 + stx

		sy = sty + 4*s
		if "B" in location:
			sy += 2*ly
		elif "M" in location:
			sy += ly 
		sx = stx +8.5*s + lx
		off = .3*s
		x1 = sx + off
		x2 = sx + 4*s - off
		y1 = sy+off
		y2 = sy +ly -off
		xfin = (x2 - x1)/2 + x1
		draw.line((xfin, y1, xfin, y2), width = int(s*4/1.25), fill=(0,0,0));
			
			
def get_characteristics(terminal):
	txt = open("../Info/dock_layout.txt")
	with open("../Info/dock_layout.txt", 'r') as f:
		lines = f.readlines()
		for k in range(0, len(lines)): 
			if terminal == "NULL":
				if "Default:" in lines[k]:
					line = lines[k]
					terminal = line[9:-1]
			elif terminal + ":"  in lines[k]:
					line = lines[k+1]
					d = int(line[7:])
	
					line = lines[k+2]
					quantity = (len(line) - 10)/6
					i = []
					start = 0
					x = line[9:]
					for j in range(0,quantity):
						try:
							end_bay = x.index("/")
						except ValueError:
							break
						bay = int(x[start: end_bay])
						end_location = x[end_bay + 1:].index("/")
						location = x[end_bay + 1: end_location]
						end_orientation = x.index(",")
						orientation = x[end_location + 1: end_orientation]
						i.append((bay, location, orientation))	
						x = x[end_orientation + 1:]


					line = lines[k+3]
					quantity = (len(line) - 9)/4
					s = []
					start = 0
					x = line[8:]
					for j in range(0,quantity):
						try:
							end_bay = x.index("/")
						except ValueError:
							break
						bay = int(x[start: end_bay])
						end_location = x.index(",")
						location = x[end_bay + 1: end_location]
						s.append((bay, location))			
						x = x[end_location + 1:]

	return d, i, s
	

def get_values(integer):
	retval = []
	run = 1
	while(run):
		string = sys.stdin.readline()
		if(string == "END\n"):
			run = 0
		else:
			if(integer):
				string = int(string)
			else:
				string = string[:-1]
			retval.append(string)
			
	return retval
	
	

	

	

s = 8								#scale
h = 24

try:
	terminal = sys.argv[1]
except:
	terminal = "NULL"
try:
	display = (sys.argv[2] == "D")
except:
	display = 0;



ds = get_values(1)
arg = get_values(0)

number_doors, I, S = get_characteristics(terminal);
dl = s*(number_doors*5/2 +1)   										#dock width
image = Image.open("../Images/load_plan.png");

bx = image.size[0] - dl - s*2
try:
	by = int(sys.argv[2])
except:
	by = image.size[1] - s*h - s*2															#border
	
d = [[1 for x in range(1000)] for x in range(1000)]

for i in range(100, 900):
	d[100][i] = 0
	d[i][100] = 0
	d[999 - i][900] = 0
	d[900][999 - i] = 0


d = map(lambda x: map(int, x), d)

draw = ImageDraw.Draw(image)
font = ImageFont.truetype("../TextFormats/FreeMonoOblique.ttf", 25)


outline(s, dl, h, bx, by)
doors(h, number_doors, bx,by)
full_bay(s, bx, by, number_doors, h)
half_bay(s, dl, bx, by, h)
set_numbers(number_doors, s, bx, by, h)
set_bay_numbers(arg, number_doors, bx, by)
#ds = [22,23, 28, 10, 18, 19, 27, 25, 15, 3]
circle_doors(ds, h, bx, by, s)

draw_island(I, image, bx, by, h, s)

draw_scale(S, h, bx, by, s)


f = open('../Images/Dock_Layout.png', 'wb')
image.save(f, "PNG")
f.close()

if(display):
	original = Image.open("../Images/Dock_Layout.png")
	width, height = original.size
	margin = 4*s
	left = bx - margin
	top = by - margin
	right = width
	bottom = height
	cropped = original.crop((left, top, right, bottom))
	cropped.show()



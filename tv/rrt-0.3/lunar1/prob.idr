%!PS-Adobe-2.0 EPSF-1.2
%%Creator: idraw
%%DocumentFonts:
%%Pages: 1
%%BoundingBox: 44 190 551 696
%%EndComments

%%BeginProcSet: cmpfont.ps 1 2
% composite fonts for ASCII-EUC mixed string
% Version 1.2 1/31/1990
% Author Ken'ichi HANDA (handa@etl.go.jp)
% Anyone can freely copy, modify, distribute this program.
/copyfont {	% font-dic extra-entry-count  copyfont  font-dic
	1 index maxlength add dict begin
	{	1 index /FID ne 2 index /UniqueID ne and
		{def} {pop pop} ifelse
	} forall
	currentdict
	end
} bind def

/compositefont {	% ASCIIFontName EUCFontName  compositefont  font'
    findfont dup /FontType get 0 eq {
	12 dict begin
	    1 copyfont dup begin
		/Encoding Encoding
		FMapType dup 2 eq {
		    pop 128 128
		}{
		    5 eq {
			256 256
		    }{
			/compositefont errordict /invalidfont get exec
		    } ifelse
		} ifelse
		getinterval def
	    end
	    /eucfont exch definefont
	    exch
	    findfont 1 copyfont dup begin
		/FontMatrix FontMatrix [1 0 0 1 0 0.05] matrix concatmatrix def
	    end
	    /asciifont exch definefont
	    exch
	    /FDepVector [ 4 2 roll ] def
	    /FontType 0 def
	    /WMode 0 def
	    /FMapType 4 def
	    /FontMatrix matrix def
	    /Encoding [0 1] def
	    /FontBBox {0 0 0 0} def
	    currentdict
	end
    }{
	pop findfont 0 copyfont
    } ifelse
} def	

/slantfont {	% FontName slant-degree  slantfont  font'
    exch findfont 1 copyfont begin
    [ 1 0 4 -1 roll 1 0 0 ] FontMatrix exch matrix concatmatrix
    /FontMatrix exch def
    currentdict
    end
} def
%%EndProcSet

%%BeginProcSet: idraw 3 0
/IdrawDict 50 dict def
IdrawDict begin

/arrowHeight 8 def
/arrowWidth 4 def

/none null def
/numGraphicParameters 17 def
/stringLimit 65535 def

/Begin {
save
numGraphicParameters dict begin
} def

/End {
end
restore
} def

/SetB {
dup type /nulltype eq {
pop
false /brushRightArrow idef
false /brushLeftArrow idef
true /brushNone idef
} {
/brushDashOffset idef
/brushDashArray idef
0 ne /brushRightArrow idef
0 ne /brushLeftArrow idef
/brushWidth idef
false /brushNone idef
} ifelse
} def

/SetCFg {
/fgblue idef
/fggreen idef
/fgred idef
} def

/SetCBg {
/bgblue idef
/bggreen idef
/bgred idef
} def

/SetF {
/printSize idef
/printFont idef
} def

/SetP {
dup type /nulltype eq {
pop true /patternNone idef
} {
dup -1 eq {
/patternGrayLevel idef
/patternString idef
} {
/patternGrayLevel idef
} ifelse
false /patternNone idef
} ifelse
} def

/BSpl {
0 begin
storexyn
newpath
n 1 gt {
0 0 0 0 0 0 1 1 true subspline
n 2 gt {
0 0 0 0 1 1 2 2 false subspline
1 1 n 3 sub {
/i exch def
i 1 sub dup i dup i 1 add dup i 2 add dup false subspline
} for
n 3 sub dup n 2 sub dup n 1 sub dup 2 copy false subspline
} if
n 2 sub dup n 1 sub dup 2 copy 2 copy false subspline
patternNone not brushLeftArrow not brushRightArrow not and and { ifill } if
brushNone not { istroke } if
0 0 1 1 leftarrow
n 2 sub dup n 1 sub dup rightarrow
} if
end
} dup 0 4 dict put def

/Circ {
newpath
0 360 arc
patternNone not { ifill } if
brushNone not { istroke } if
} def

/CBSpl {
0 begin
dup 2 gt {
storexyn
newpath
n 1 sub dup 0 0 1 1 2 2 true subspline
1 1 n 3 sub {
/i exch def
i 1 sub dup i dup i 1 add dup i 2 add dup false subspline
} for
n 3 sub dup n 2 sub dup n 1 sub dup 0 0 false subspline
n 2 sub dup n 1 sub dup 0 0 1 1 false subspline
patternNone not { ifill } if
brushNone not { istroke } if
} {
Poly
} ifelse
end
} dup 0 4 dict put def

/Elli {
0 begin
newpath
4 2 roll
translate
scale
0 0 1 0 360 arc
patternNone not { ifill } if
brushNone not { istroke } if
end
} dup 0 1 dict put def

/Line {
0 begin
2 storexyn
newpath
x 0 get y 0 get moveto
x 1 get y 1 get lineto
brushNone not { istroke } if
0 0 1 1 leftarrow
0 0 1 1 rightarrow
end
} dup 0 4 dict put def

/MLine {
0 begin
storexyn
newpath
n 1 gt {
x 0 get y 0 get moveto
1 1 n 1 sub {
/i exch def
x i get y i get lineto
} for
patternNone not brushLeftArrow not brushRightArrow not and and { ifill } if
brushNone not { istroke } if
0 0 1 1 leftarrow
n 2 sub dup n 1 sub dup rightarrow
} if
end
} dup 0 4 dict put def

/Poly {
3 1 roll
newpath
moveto
-1 add
{ lineto } repeat
closepath
patternNone not { ifill } if
brushNone not { istroke } if
} def

/Rect {
0 begin
/t exch def
/r exch def
/b exch def
/l exch def
newpath
l b moveto
l t lineto
r t lineto
r b lineto
closepath
patternNone not { ifill } if
brushNone not { istroke } if
end
} dup 0 4 dict put def

/Text {
ishow
} def

/idef {
dup where { pop pop pop } { exch def } ifelse
} def

/ifill {
0 begin
gsave
patternGrayLevel -1 ne {
fgred bgred fgred sub patternGrayLevel mul add
fggreen bggreen fggreen sub patternGrayLevel mul add
fgblue bgblue fgblue sub patternGrayLevel mul add setrgbcolor
eofill
} {
eoclip
originalCTM setmatrix
pathbbox /t exch def /r exch def /b exch def /l exch def
/w r l sub ceiling cvi def
/h t b sub ceiling cvi def
/imageByteWidth w 8 div ceiling cvi def
/imageHeight h def
bgred bggreen bgblue setrgbcolor
eofill
fgred fggreen fgblue setrgbcolor
w 0 gt h 0 gt and {
l w add b translate w neg h scale
w h true [w 0 0 h neg 0 h] { patternproc } imagemask
} if
} ifelse
grestore
end
} dup 0 8 dict put def

/istroke {
gsave
brushDashOffset -1 eq {
[] 0 setdash
1 setgray
} {
brushDashArray brushDashOffset setdash
fgred fggreen fgblue setrgbcolor
} ifelse
brushWidth setlinewidth
originalCTM setmatrix
stroke
grestore
} def

/ishow {
0 begin
gsave
fgred fggreen fgblue setrgbcolor
/fontDict printFont printSize scalefont dup setfont def
/descender fontDict begin 0 [FontBBox] 1 get FontMatrix end
transform exch pop def
/vertoffset 1 printSize sub descender sub def {
0 vertoffset moveto show
/vertoffset vertoffset printSize sub def
} forall
grestore
end
} dup 0 3 dict put def
/patternproc {
0 begin
/patternByteLength patternString length def
/patternHeight patternByteLength 8 mul sqrt cvi def
/patternWidth patternHeight def
/patternByteWidth patternWidth 8 idiv def
/imageByteMaxLength imageByteWidth imageHeight mul
stringLimit patternByteWidth sub min def
/imageMaxHeight imageByteMaxLength imageByteWidth idiv patternHeight idiv
patternHeight mul patternHeight max def
/imageHeight imageHeight imageMaxHeight sub store
/imageString imageByteWidth imageMaxHeight mul patternByteWidth add string def
0 1 imageMaxHeight 1 sub {
/y exch def
/patternRow y patternByteWidth mul patternByteLength mod def
/patternRowString patternString patternRow patternByteWidth getinterval def
/imageRow y imageByteWidth mul def
0 patternByteWidth imageByteWidth 1 sub {
/x exch def
imageString imageRow x add patternRowString putinterval
} for
} for
imageString
end
} dup 0 12 dict put def

/min {
dup 3 2 roll dup 4 3 roll lt { exch } if pop
} def

/max {
dup 3 2 roll dup 4 3 roll gt { exch } if pop
} def

/midpoint {
0 begin
/y1 exch def
/x1 exch def
/y0 exch def
/x0 exch def
x0 x1 add 2 div
y0 y1 add 2 div
end
} dup 0 4 dict put def

/thirdpoint {
0 begin
/y1 exch def
/x1 exch def
/y0 exch def
/x0 exch def
x0 2 mul x1 add 3 div
y0 2 mul y1 add 3 div
end
} dup 0 4 dict put def

/subspline {
0 begin
/movetoNeeded exch def
y exch get /y3 exch def
x exch get /x3 exch def
y exch get /y2 exch def
x exch get /x2 exch def
y exch get /y1 exch def
x exch get /x1 exch def
y exch get /y0 exch def
x exch get /x0 exch def
x1 y1 x2 y2 thirdpoint
/p1y exch def
/p1x exch def
x2 y2 x1 y1 thirdpoint
/p2y exch def
/p2x exch def
x1 y1 x0 y0 thirdpoint
p1x p1y midpoint
/p0y exch def
/p0x exch def
x2 y2 x3 y3 thirdpoint
p2x p2y midpoint
/p3y exch def
/p3x exch def
movetoNeeded { p0x p0y moveto } if
p1x p1y p2x p2y p3x p3y curveto
end
} dup 0 17 dict put def

/storexyn {
/n exch def
/y n array def
/x n array def
n 1 sub -1 0 {
/i exch def
y i 3 2 roll put
x i 3 2 roll put
} for
} def

/SSten {
fgred fggreen fgblue setrgbcolor
dup true exch 1 0 0 -1 0 6 -1 roll matrix astore
} def

/FSten {
dup 3 -1 roll dup 4 1 roll exch
newpath
0 0 moveto
dup 0 exch lineto
exch dup 3 1 roll exch lineto
0 lineto
closepath
bgred bggreen bgblue setrgbcolor
eofill
SSten
} def

/Rast {
exch dup 3 1 roll 1 0 0 -1 0 6 -1 roll matrix astore
} def

/arrowhead {
0 begin
transform originalCTM itransform
/taily exch def
/tailx exch def
transform originalCTM itransform
/tipy exch def
/tipx exch def
/dy tipy taily sub def
/dx tipx tailx sub def
/angle dx 0 ne dy 0 ne or { dy dx atan } { 90 } ifelse def
gsave
originalCTM setmatrix
tipx tipy translate
angle rotate
newpath
arrowHeight neg arrowWidth 2 div moveto
0 0 lineto
arrowHeight neg arrowWidth 2 div neg lineto
patternNone not {
originalCTM setmatrix
/padtip arrowHeight 2 exp 0.25 arrowWidth 2 exp mul add sqrt brushWidth mul
arrowWidth div def
/padtail brushWidth 2 div def
tipx tipy translate
angle rotate
padtip 0 translate
arrowHeight padtip add padtail add arrowHeight div dup scale
arrowheadpath
ifill
} if
brushNone not {
originalCTM setmatrix
tipx tipy translate
angle rotate
arrowheadpath
istroke
} if
grestore
end
} dup 0 9 dict put def

/arrowheadpath {
newpath
arrowHeight neg arrowWidth 2 div moveto
0 0 lineto
arrowHeight neg arrowWidth 2 div neg lineto
} def

/leftarrow {
0 begin
y exch get /taily exch def
x exch get /tailx exch def
y exch get /tipy exch def
x exch get /tipx exch def
brushLeftArrow { tipx tipy tailx taily arrowhead } if
end
} dup 0 4 dict put def

/rightarrow {
0 begin
y exch get /tipy exch def
x exch get /tipx exch def
y exch get /taily exch def
x exch get /tailx exch def
brushRightArrow { tipx tipy tailx taily arrowhead } if
end
} dup 0 4 dict put def

end
%%EndProcSet
%%EndProlog

%%BeginSetup
IdrawDict begin

%%EndSetup

%I Idraw 10 Grid 8 8 

%%Page: 1 1

Begin
%I b u
%I cfg u
%I cbg u
%I f u
%I p u
%I t
[ 0.955325 0 0 0.955325 0 0 ] concat
/originalCTM matrix currentmatrix def

Begin %I Rect
%I b 65535
1 0 0 [] 0 SetB
%I cfg Black
0 0 0 SetCFg
%I cbg White
1 1 1 SetCBg
none SetP %I p n
%I t
[ 16 -0 -0 16 -2632 -8304 ] concat
%I
168 532 200 564 Rect
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 4
256 152
544 152
544 192
376 248
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 5
376 248
456 216
496 312
472 424
424 392
5 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 4
488 344
584 328
576 400
472 424
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 4
464 216
536 216
536 224
440 224
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 5
544 152
768 152
768 312
632 240
544 192
5 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
768 312
752 392
624 232
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 16 312 ] concat
%I 4
464 216
536 216
536 224
440 224
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 5
752 392
744 424
632 544
568 520
680 408
5 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
752 392
680 408
704 320
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 4
632 544
584 576
488 584
344 576
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
632 544
448 568
568 520
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 4
344 576
400 544
480 552
464 568
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 4
344 576
336 512
392 496
400 544
4 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
336 512
360 456
392 496
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
344 576
400 600
472 576
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
528 576
488 608
440 584
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
584 328
600 352
576 400
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
584 360
600 384
576 400
3 Poly
End

Begin %I Poly
%I b 65535
1 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg Black
0 0 0 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -200 56 ] concat
%I 3
256 152
312 192
256 248
3 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -32 60 ] concat
%I 4
600 148
608 148
608 668
600 668
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -32 60 ] concat
%I 4
600 668
80 668
80 660
600 660
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -32 60 ] concat
%I 4
80 660
80 140
88 140
88 660
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 1 -0 -0 1 -32 60 ] concat
%I 4
88 140
608 140
608 148
88 148
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
184 388
112 388
112 348
184 348
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
120 348
112 324
120 324
128 348
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
184 324
176 348
168 348
176 324
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 5
120 324
96 324
96 316
128 316
128 324
5 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
200 324
168 324
168 316
200 316
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
144 348
136 332
160 332
152 348
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
184 388
176 396
120 396
112 388
4 Poly
End

Begin %I Poly
%I b 65535
0 0 0 [] 0 SetB
%I cfg DkGray
0.503548 0.503548 0.503548 SetCFg
%I cbg White
1 1 1 SetCBg
%I p
0 SetP
%I t
[ 0.25068 0 0 0.25068 25.8993 122.755 ] concat
%I 4
168 396
168 404
128 404
128 396
4 Poly
End

End %I eop

showpage

%%Trailer

end
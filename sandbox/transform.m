t = [3, 3]
s = [1, 2]
r = -pi / 2


mw = [
  s(1) * cos( r ), -s(2) * sin( r ), t(1);
  s(1) * sin( r ),  s(2) * cos( r ), t(2);
  0, 0, 1
]

mo = [
  1 / s(1) * cos( -r ), - 1 / s(1) * sin( -r ), -1 / s(1) * (t(1) * cos(-r) - t(2) * sin(-r));
  1 / s(2) * sin( -r ),   1 / s(2) * cos( -r ), -1 / s(2) * (t(1) * sin(-r) + t(2) * cos(-r));
  0, 0, 1
]

%  m = [
%    s(1) * cos(r), -s(1) * sin(r), s(1) * (cos(r) * t(1) - sin(r) * t(2) ) - s(1) * t(1);
%    s(2) * sin(r),  s(2) * cos(r), s(2) * (sin(r) * t(1) + cos(r) * t(2) ) - s(2) * t(2);
%    0, 0, 1
%  ]

%  mt1 = [
%    1, 0, -t(1);
%    0, 1, -t(2);
%    0, 0, 1
%  ]
%  
%  mt = [
%    1, 0, t(1);
%    0, 1, t(2);
%    0, 0, 1
%  ]
%  
%  ms = [
%    s(1), 0, 0;
%    0, s(2), 0;
%    0, 0, 1
%  ]
%  
%  ms1 = [
%    1 / s(1), 0, 0;
%    0, 1 / s(2), 0;
%    0, 0, 1
%  ]
%  
%  mr = [
%    cos(r), -sin(r), 0;
%    sin(r),  cos(r), 0;
%    0, 0, 1
%  ]
%  
%  mr1 = [
%    cos(-r), -sin(-r), 0;
%    sin(-r),  cos(-r), 0;
%    0, 0, 1
%  ]
%  
%  mw = mt  * mr  * ms
%  mo = ms1 * mr1 * mt1

p = [2, 1]

world  = mw  * [p(1), p(2), 1]'
object = mo * [5, 1, 1]'


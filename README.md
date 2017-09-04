# happyacro-dos

A c++ motivational acronym generator.

This program creates motivational acronyms for an acronym you specify. 

It's not going to print out every generated acronym. It's basically a funny / shitty benchmark joke for a [book](http://www.happyacro.com).

This program's purpose is to run on [DOSBox](https://www.dosbox.com/) while emulating old PCs [XT/286/386/486 etc).


# Building

If you want to build the program on modern hardware. Install gcc on your system and run `gcc happyacro.cpp -o happyacro` to build it.

But, I was trying to run this thing on DOSBox, which is an emulator for old versions of MS-DOS. That required a number of hoops to jump through for building it:

# Building The Masochistic Version For DOSBox

1. I tried to compile the c++ version with djgpp, turbo c++ (various versions), microsoft c/c++ (various versions), bordland c++ on dosbox, watcom, and others. Don't bother.
2. Learned that c++ standard library wasn't standardized until after the products mentioned above existed.
3. Didn't want to write some weird compiler-specific c++ variant, so decided to write in C. 
4. Fired up a windows 98 virtual box image [Instructions here](https://forums.virtualbox.org/viewtopic.php?f=2&t=59559).
   - pro tip: [winworldpc.com](https://winworldpc.com/) and [oldversion.com](http://www.oldversion.com/) are your friends for finding win98 images and old software. 
   - pro tip: OSX use [this](https://superuser.com/a/85991) to make ISO images with installers, then mount the ISO as a cd-rom on VirtualBox to copy the files to Win98. 
   - pro tip: Or, [start an http server](http://lifehacker.com/start-a-simple-web-server-from-any-directory-on-your-ma-496425450) on your box and hit that from within win98.
   - pro tip: Win98's ssl encryption types are horrendously out of date, so you won't be able to hit almost any websites from within the image. 
   - pro tip: To ftp over from OSX, first install [FileZilla 2.2.20](http://www.oldversion.com/windows/filezilla-2-2-20) (other versions won't work), then [enable FTP on OSX](https://gaborhargitai.hu/enable-built-in-ftp-server-in-mac-os-x-yosemite-el-capitan-sierra/).
5. Installed [Open Watcom 1.9](http://www.openwatcom.org) on the Win98 image.
6. Created an Open Watcom project with a target environment of "Dos - 32-bit" and Image Type "Causeway Executable [.exe]".
7. Wrote the c version of the program, compiling and checking if it'd work in the DOSBox image along the way. 
8. Built the c version, ftped it over to my OSX box in my dosbox directory, and ran it in DOSBox. 

# Running

Usage is as follows: 

	USAGE: happyacro <acronym>  <reporting interval> <word file>

- the acronym is the motivational acronym you want to generate from such as TEAM
- the reporting interval controls how often output is generated
- the word file is a file containing words to use, one word per line

# Running on an [emulated] old box

Instructions for tuning dosbox emulation to emulate an 8086 [or 80386) accurately: 

https://www.dosbox.com/wiki/4.77_MHz

Check [here](https://en.wikipedia.org/wiki/List_of_Intel_microprocessors) to see the mhz of various old computers.

NOTE: Keep in mind that x86 processors weren't 32 bit until the 386, so we're technically cheating when we run a the 32-bit version of the program on DOSBox at a speed below 386 to emulate older hardware.

# Fun Facts

I received the following results running this program: 

- Emulated Machine: 1979 8086 @ 5MHz (DOSBox Cycle Setting: 250 cycles). Output: 315 acronyms per second.
- Emulated Machine: 1982 80286 @ 12MHz (DOSBox Cycle Setting: 1250 cycles). Output: 1,580 acronyms per second.
- Emulated Machine: 1985 80386 @ 33MHz (DOSBox Cycle Setting: 3250 cycles). Output: 4,100 acronyms per second.
- Emulated Machine: 1989 80486 @ 66MHz (DOSBox Cycle Setting: 7250 cycles). Output: 9,100 acronyms per second.
- Emulated Machine: 1992 80486DX2 @ 100MHz (DOSBox Cycle Setting: 12750 cycles). Output: 15,500 acronyms per second.
- Emulated Machine: 1997 Pentium 1 @ 166MHz (DOSBox Cycle Setting: 20500 cycles). Output: 24,800 acronyms per second.  
- Non-emulated Machine: 2014 MacBookPro11,2 Intel(R) Core(TM) i7-4980HQ CPU @ 2.80GHz (single threaded). Output: 2,000,000 acronyms per second.

*Run configuration:*

- All runs were done with the word "team" as the acronym
- Word file is from [here](https://github.com/dwyl/english-words). It has ~470K words in a 4MB text file.
- I ran with print frequency of 100,000.

*Emulated Environment Notes*

- Environment: DOSBox 0.74 running on MacBook Pro Late 2014 15" model.
- I used the [TOPBENCH](https://dosbenchmark.wordpress.com/) instead of MIPS.COM program as directed [here](ttps://www.dosbox.com/wiki/4.77_MHz) and played with the configured cycle count to get DOSBox operating close to the desired clock speed for each run. MIPS.COM's math gets funny after the multiplier goes over 25x. 
- Executable for emulated machines was compiled with the open watcom 1.9 compiler mentioned earlier in this document.

*Non-Emulated Enviornment Notes*

- Executable for non-emulated machine was compiled with `g++ happyacro.cpp` (gcc didn't like undefined _max fn in the .c version, so I was lazy and compiled .cpp, whatever).

# License

All scripts are licensed with the [Apache license](http://en.wikipedia.org/wiki/Apache_license), which is a great license because, essentially it:

* a) covers liability - my code should work, but I'm not liable if you do something stupid with it
* b) allows you to copy, fork, and use the code, even commercially
* c) is [non-viral](http://en.wikipedia.org/wiki/Viral_license), that is, your derivative code doesn't *have to be* open source to use it

Other great licensing options for your own code: [BSD License](https://en.wikipedia.org/wiki/BSD_licenses), [MIT License](https://en.wikipedia.org/wiki/MIT_License), or [Creative Commons](https://en.wikipedia.org/wiki/Creative_Commons_license).

Here's the license:

Copyright [c) 2017, Coder Cowboy, LLC. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
  
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
[INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
[INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  
The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied.
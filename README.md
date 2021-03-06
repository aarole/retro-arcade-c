# Retro Arcade

This program provides a collection of retro games created in ANSI C.

The games included in this program are:
<ul>
  <li>PAC-Man</li>
  <li>Minesweeper</li>
  <li>Tic-Tac-Toe</li>
  <li>Rock, Paper, Scissors</li>
  <li>Snake (Pending)</li>
</ul>

# Dependencies
<ul>
  <li>cJSON</li>
  <li>libcurl</li>
</ul>
The dependencies are either included with the program or are present in the distro's official repositories<br>
NOTE: libcurl-dev is not always installed by default
<ul>
  <li>Ubuntu 20.04 requires installation using <i>sudo apt install libcurl4-gnutls-dev</i></li>
<li>Arch linux has curl in its core, it should be installed automatically. If not, use <i>sudo pacman -S curl</i></li>
</ul>

# Downloading the program
This program can be downloaded with:
<ul>
  <li><i>git clone https://github.com/aarole/retro-arcade-c.git</i></li>
</ul>

# Compiling the program
This program can be compiled by following the steps below:
<ul>
  <li><i>cd retro-arcade-c</i></li>
  <li><i>make --always-make</i></li>
</ul>

# Running the program
This program can be run following the steps below:
<ul>
  <li>Ensure you are in the <i>retro-arcade-c</i> directory</li>
  <li><i>./main<i></li>
</ul>

# newImg / nimg
Multi-platform solution to create new images right from your terminal.
Officially supports Windows and Linux
# How to use it?
## Windows
### From File Explorer
* set nimg as the default program for .nimg files
* create a new file using this format: `filename.WIDTHxHEIGHT.extension.nimg`
* double click the file to create the image
### From the Terminal
* add the nimg executable to PATH (not required but recommended)
* run `nimg filename.WIDTHxHEIGHT.extension` (you dont need the .nimg here)
## Linux
### Adding to PATH (using nimg from the terminal)
Move `nimg` to a folder you remember, like `/opt/user/`

Then in your .bashrc or .zshrc (or other) add a similar line to:

`export PATH="/opt/user/:PATH"`

This will export the directory to PATH. (Make sure the location exists, also user can be anything)

---

Now, just run `nimg filename.WIDTHxHEIGHT.extension`

## How to set as default?
There are probably several ways to do it, but I use this one:
* create a .nimg file. doesn't matter what it's called or what it contains, just create it.
* now, right click on the file, click "open with" and select "choose another app".
* navigate to the nimg executable and select it.
* make sure you select "always use this app to open .nimg files"
* now, whenever you double click a .nimg file, it will open in nimg.
## Exit Codes
* 0: success
* 1: incorrect argument amount
* 2: error deleting file
* 3: error saving image
* 4: other error

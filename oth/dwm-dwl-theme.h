//SETTINGS
//[python_data start]( name = FONT)
#define FONT "JetBrains Mono Medium"
#define FONT_SIZE 10
//[python_data end]

//Windows border
//[python_data start]( name = NORMAL_WINDOW_COLOR)
#define NORMAL_WINDOW_COLOR_R 3A
#define NORMAL_WINDOW_COLOR_G 6E
#define NORMAL_WINDOW_COLOR_B A5
//[python_data end]

//[python_data start]( name = SELECTED_WINDOW_COLOR)
#define SELECTED_WINDOW_COLOR_R FF
#define SELECTED_WINDOW_COLOR_G 67
#define SELECTED_WINDOW_COLOR_B 00
//[python_data end]

//Bar

//[python_data start]( name = NORAML_BACKGROUND_COLOR )
#define NORAML_BACKGROUND_COLOR_R 00
#define NORAML_BACKGROUND_COLOR_G 4E
#define NORAML_BACKGROUND_COLOR_B 98
//[python_data end]

//[python_data start]( name = NORMAL_FONT_COLOR )
#define NORMAL_FONT_COLOR_R C0
#define NORMAL_FONT_COLOR_G C0
#define NORMAL_FONT_COLOR_B C0
//[python_data end]

//[python_data start]( name = SELECTED_BACKGROUND_COLOR )
#define SELECTED_BACKGROUND_COLOR_R FF
#define SELECTED_BACKGROUND_COLOR_G 67
#define SELECTED_BACKGROUND_COLOR_B 00
//[python_data end]

//[python_data start]( name = SELECTED_FONT_COLOR )
#define SELECTED_FONT_COLOR_R EB
#define SELECTED_FONT_COLOR_G EB
#define SELECTED_FONT_COLOR_B EB
//[python_data end]

//highlight bar (fzf)
//[python_data start]( name = NORAML_BACKGROUND_HIGHLIGHT_COLOR )
#define NORAML_BACKGROUND_HIGHLIGHT_COLOR_R 00
#define NORAML_BACKGROUND_HIGHLIGHT_COLOR_G 4E
#define NORAML_BACKGROUND_HIGHLIGHT_COLOR_B 98
//[python_data end]

//[python_data start]( name = NORMAL_FONT_HIGHLIGHT_COLOR )
#define NORMAL_FONT_HIGHLIGHT_COLOR_R 4E
#define NORMAL_FONT_HIGHLIGHT_COLOR_G 73
#define NORMAL_FONT_HIGHLIGHT_COLOR_B 90
//[python_data end]

//[python_data start]( name = SELECTED_BACKGROUND_HIGHLIGHT_COLOR )
#define SELECTED_BACKGROUND_HIGHLIGHT_COLOR_R FF
#define SELECTED_BACKGROUND_HIGHLIGHT_COLOR_G 67
#define SELECTED_BACKGROUND_HIGHLIGHT_COLOR_B 00
//[python_data end]

//[python_data start]( name = SELECTED_FONT_HIGHLIGHT_COLOR )
#define SELECTED_FONT_HIGHLIGHT_COLOR_R 4E
#define SELECTED_FONT_HIGHLIGHT_COLOR_G 73
#define SELECTED_FONT_HIGHLIGHT_COLOR_B 90
//[python_data end]


//MACROS
//to dwm
#define ____DWM_COLOR(r, g, b) "#" #r #g #b
#define __DWM_COLOR(r, g, b) ____DWM_COLOR(r, g, b)
#define DWM_COLOR(name) __DWM_COLOR(name##_R, name##_G, name##_B)

#define __DWM_GET_FONT(fn, sz) fn ":size=" #sz
#define DWM_GET_FONT(fn, sz) __DWM_GET_FONT(fn, sz)


#define DWM_BAR_FONT DWM_GET_FONT(FONT, FONT_SIZE)

//to dwl
#define ______DWL_COLOR(r, g, b) { r/255.0, g/255.0, b/255.0, 1.0}
#define ____DWL_COLOR(r, g, b) ______DWL_COLOR(0x##r, 0x##g, 0x##b)
#define __DWL_COLOR(r, g, b) ____DWL_COLOR(r, g, b)
#define DWL_COLOR(name) __DWL_COLOR(name##_R, name##_G, name##_B)

#define ______DWL_BAR_COLOR(r, g, b) { r, g, b, 255}
#define ____DWL_BAR_COLOR(r, g, b) ______DWL_BAR_COLOR(0x##r, 0x##g, 0x##b)
#define __DWL_BAR_COLOR(r, g, b) ____DWL_BAR_COLOR(r, g, b)
#define DWL_BAR_COLOR(name) __DWL_BAR_COLOR(name##_R, name##_G, name##_B)

#define __DWL_GET_FONT(fn, sz) fn " " #sz
#define DWL_GET_FONT(fn, sz) __DWL_GET_FONT(fn, sz)


#define DWL_BAR_FONT DWL_GET_FONT(FONT, FONT_SIZE)





//PYTHON settings menu
/*
//[python_code start]


colors=dict()
def add_color(d, name):
    global colors
    col_r=d.data.split("\n")[0].split(" ")[-1]
    col_g=d.data.split("\n")[1].split(" ")[-1]
    col_b=d.data.split("\n")[2].split(" ")[-1]
    col="#"+col_r+col_g+col_b
    colors[name]=col

print(this_file_name)


add_color(NORMAL_WINDOW_COLOR, "NORMAL_WINDOW_COLOR")
add_color(SELECTED_WINDOW_COLOR, "SELECTED_WINDOW_COLOR")
add_color(NORAML_BACKGROUND_COLOR, "NORAML_BACKGROUND_COLOR")
add_color(NORMAL_FONT_COLOR, "NORMAL_FONT_COLOR")
add_color(SELECTED_BACKGROUND_COLOR, "SELECTED_BACKGROUND_COLOR")
add_color(SELECTED_FONT_COLOR, "SELECTED_FONT_COLOR")
add_color(NORAML_BACKGROUND_HIGHLIGHT_COLOR, "NORAML_BACKGROUND_HIGHLIGHT_COLOR")
add_color(NORMAL_FONT_HIGHLIGHT_COLOR, "NORMAL_FONT_HIGHLIGHT_COLOR")
add_color(SELECTED_FONT_HIGHLIGHT_COLOR, "SELECTED_FONT_HIGHLIGHT_COLOR")
add_color(SELECTED_BACKGROUND_HIGHLIGHT_COLOR, "SELECTED_BACKGROUND_HIGHLIGHT_COLOR")

font=dict()
font["font"]=FONT.data.split("\n")[0].split(" ", 2)[-1].replace('"','')
font["size"]=FONT.data.split("\n")[1].split(" ", 2)[-1]
print(font)


import tkinter as tk
from tkinter import ttk
from functools import partial

# root window
root = tk.Tk()
root.geometry("900x450")
root.title('settings')
root.resizable(0, 0)

# configure the grid
root.columnconfigure(0, weight=1)
root.columnconfigure(1, weight=3)



#font 15
#screen width 1920
#screen height 1200
#window width 1918
#window height 1168
#window width + border 1920
#window height + border 1170
#bar 30
#
#font 13
#screen width 1920
#screen height 1200
#window width 1918
#window height 1172
#window width + border 1920
#window height + border 1174
#bar 26
#
#font 12
#screen width 1920
#screen height 1200
#window width 1918
#window height 1174
#window width + border 1920
#window height + border 1176
#bar 24
#
#font 11
#screen width 1920
#screen height 1200
#window width 1918
#window height 1176
#window width + border 1920
#window height + border 1178
#bar 22
#
#font 10
#screen width 1920
#screen height 1200
#window width 1918
#window height 1178
#window width + border 1920
#window height + border 1180
#bar 20


def ch_col(n):
    global colors
    from tkinter.colorchooser import askcolor
    col = askcolor(color=colors[n], title=n)
    if col[1]:
        print(n+": "+colors[n]+" new: "+col[1])
        colors[n]=col[1]

# Color buttons
r=0
for n in colors:
    ttk.Button(root, text=n, command=partial(ch_col,n)).grid(column=0, row=r, sticky=tk.W, padx=1, pady=1)
    r+=1

canvas = tk.Canvas(root, width=600, height=400, bg='black')
canvas.grid(column=1, row=0, rowspan=10)

canvas.create_rectangle((0, 0), (300, 2*int(font["size"])), fill=colors["NORAML_BACKGROUND_COLOR"],width=0)
canvas.create_rectangle((300, 0), (601, 2*int(font["size"])), fill=colors["NORAML_BACKGROUND_HIGHLIGHT_COLOR"],width=0)
canvas.create_rectangle((1, 2*int(font["size"])), (300-1, 400), outline=colors["SELECTED_WINDOW_COLOR"], fill="gray")
canvas.create_rectangle((300, 2*int(font["size"])+0), (600, 200), outline=colors["NORMAL_WINDOW_COLOR"], fill="gray")
canvas.create_rectangle((300, 201), (600, 400), outline=colors["NORMAL_WINDOW_COLOR"], fill="gray")
canvas.create_text(
    (0, int(font["size"])),
    text="1 2 3",
    fill="orange",
    font="JetBrains "+font["size"]
)
root.mainloop()


//[python_code end]
*/

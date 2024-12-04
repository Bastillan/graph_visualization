import tkinter as tk
from calculations import *

def calculate(coordinates):
    x = int(x_input.get())
    a = int(a_input.get())
    b = int(b_input.get())
    y_value = y(x, a, b)
    y_output.configure(text=f"y = {y_value}")
    my_canvas.create_oval(coordinates[0]+x*20-3, coordinates[1]-y_value*20-3, coordinates[0]+x*20+3, coordinates[1]-y_value*20+3, fill="red")

def draw_coordinate_system(canva, coordinates, size):
    line_width = 2
    space = 20
    # canva.create_line(0, 100, 300, 100, fill="black")
    # drawing vertical line
    canva.create_line(coordinates[0], coordinates[1], coordinates[0], coordinates[1] - size, fill="black", width=line_width)
    # drawing horizontal line
    canva.create_line(coordinates[0], coordinates[1], coordinates[0] + size, coordinates[1], fill="black", width=line_width)
    # drawing vertical scale
    for y in range(coordinates[1] - space, coordinates[1] - size, -space):
        canva.create_line(coordinates[0]-5, y, coordinates[0]+5, y, fill="black", width=line_width)
    # drawing horizontal scale
    for x in range(coordinates[0] + space, coordinates[0] + size, +space):
        canva.create_line(x, coordinates[1]-5, x, coordinates[1]+5, fill="black", width=line_width)


if __name__ == "__main__":
    window = tk.Tk()
    window.title("Graph viewer prototype")
    window.geometry("400x500")
    coordinates_start = (10, 390)

    in_label = tk.Label(window, text = "Input x, a, b: ")
    in_label.grid(column=0, row=0)

    x_input = tk.Entry(window, width=10)
    x_input.grid(column=1, row=0)
    a_input = tk.Entry(window, width=10)
    a_input.grid(column=2, row=0)
    b_input = tk.Entry(window, width=10)
    b_input.grid(column=3, row=0)

    lbl = tk.Label(window, text = f"y = a * x + b")
    lbl.grid(column=0, row=1)

    button = tk.Button(window, text = "Calculate", command=lambda : calculate(coordinates_start))
    button.grid(column=0, row=2)
    
    y_output = tk.Label(window, text = "y =")
    y_output.grid(column=0, row=3)

    my_canvas = tk.Canvas(window, width=400, height=400, bg="white")
    my_canvas.grid(column=0,row=4,columnspan=4)
    draw_coordinate_system(my_canvas, coordinates_start, 390)

    window.mainloop()

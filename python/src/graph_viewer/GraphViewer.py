import tkinter as tk
from tkinter import filedialog
from graphs import *

class GraphViewer():
    def __init__(self):
        self.plugin_path=""
        self.start_coordinates = (10, 390)

        self.window = tk.Tk()
        self.window.title("Graph viewer")
        self.window.geometry("1000x800")

        self.menu_bar = tk.Menu(self.window)
        self.file_menu = tk.Menu(self.menu_bar, tearoff=0)
        self.file_menu.add_command(label="New", command=self.create_new_graph)
        self.file_menu.add_command(label="Open graph", command=self.open_graph)
        self.file_menu.add_command(label="Load plugin", command=self.load_plugin)
        self.file_menu.add_command(label="Save")
        # self.file_menu.add_separator()  # Separator
        self.menu_bar.add_cascade(label="File", menu=self.file_menu)
        self.window.config(menu=self.menu_bar)

        self.new_node_button = tk.Button(self.window, text="Add node")
        self.new_node_button.grid(column=0, row=0)
        self.delete_node_button = tk.Button(self.window, text="Delete node")
        self.delete_node_button.grid(column=1, row=0)
        self.group_nodes_button = tk.Button(self.window, text="Group nodes")
        self.group_nodes_button.grid(column=2, row=0)
        self.zoom_in_button = tk.Button(self.window, text="+")
        self.zoom_in_button.grid(column=3, row=0)
        self.zoom_out_button = tk.Button(self.window, text="-")
        self.zoom_out_button.grid(column=4, row=0)
        self.canva = tk.Canvas(self.window, width=400, height=400, bg="white")
        self.canva.grid(column=0, row=1, columnspan=5)

    def start(self):
        self.window.mainloop()

    def load_plugin(self):
        self.plugin_path = filedialog.askopenfilename(
        title="Choose plugin",
        # filetypes=[("Pliki tekstowe", "*.txt"), ("Wszystkie pliki", "*.*")]
        )

    def open_graph(self):
        self.graph_path = filedialog.askopenfilename(title="Choose graph")
        self.graph = load_graph(self.graph_path)

    def create_new_graph(self):
        new_graph_path = filedialog.asksaveasfilename(title="Enter new graph name")
        if new_graph_path:
            try:
                with open(new_graph_path, "w") as file:
                    file.write("")
                self.graph_path = new_graph_path
            except Exception as e:
                print(f"Error: {e}")

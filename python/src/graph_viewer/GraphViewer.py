import tkinter as tk
from tkinter import filedialog
from graphs import *

class GraphViewer():
    def __init__(self):
        self.plugin_path="../cpp/app/plugins/libplugin.so"
        self.canva_size = (1000, 700)
        self.start_coordinates = (100, 100)
        self.vertice_size = 60
        self.vertice_color = "blue"
        self.edge_width = 2
        self.edge_color = "red"
        self.text_size = 10
        self.text_color="black"
        self.scale = 200
        self.vertices = []
        self.vertices_coordinates = []
        self.edges=[]
        self.graph = []

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
        self.zoom_in_button = tk.Button(self.window, text="+", command=self.zoom_in)
        self.zoom_in_button.grid(column=3, row=0)
        self.zoom_out_button = tk.Button(self.window, text="-", command=self.zoom_out)
        self.zoom_out_button.grid(column=4, row=0)
        self.canva = tk.Canvas(self.window, width=self.canva_size[0], height=self.canva_size[1], bg="white")
        self.canva.grid(column=0, row=1, columnspan=5)
        self.canva.bind("<Button-4>", self.on_scroll)
        self.canva.bind("<Button-5>", self.on_scroll)


    def start(self):
        self.window.mainloop()

    def load_plugin(self):
        self.plugin_path = filedialog.askopenfilename(
        title="Choose plugin",
        )

    def open_graph(self):
        self.graph_path = filedialog.askopenfilename(title="Choose graph")
        self.graph = loadGraph(self.graph_path)
        self.vertices = self.graph.getVerticesData()
        self.vertices_coordinates = calculateLayout(self.graph, self.plugin_path)
        self.edges = self.graph.getEdges()
        self.draw()

    def create_new_graph(self):
        new_graph_path = filedialog.asksaveasfilename(title="Enter new graph name")
        if new_graph_path:
            try:
                with open(new_graph_path, "w") as file:
                    file.write("")
                self.graph_path = new_graph_path
            except Exception as e:
                print(f"Error: {e}")

    def zoom_in(self):
        self.scale += 10
        self.draw()

    def zoom_out(self):
        self.scale -= 10
        self.draw()

    def on_scroll(self, event):
        if event.delta != 0:
            if event.delta > 0:
                self.scale += 10
                print("zoom_in")
            else:
                self.scale -= 10
                print("zoom_out")
        else:
            if event.num == 4:
                self.zoom_in()
            if event.num == 5:
                self.zoom_out()


    def draw(self):
        self.canva.delete("all")
        for edge in self.edges:
            edge_start = self.vertices_coordinates.get(edge[0])
            edge_end = self.vertices_coordinates.get(edge[1])
            edge_start = (edge_start[0]*self.scale, edge_start[1]*self.scale)
            edge_end = (edge_end[0]*self.scale, edge_end[1]*self.scale)
            print(edge_start, edge_end)
            self.draw_line(edge_start, edge_end)

        for vertice in self.vertices_coordinates:
            x, y = self.vertices_coordinates[vertice]
            text = self.vertices[vertice]
            x = x * self.scale
            y = y * self.scale
            self.draw_circle(x, y)
            self.write_text(x, y, text)

        for vertice in self.vertices:
            print(self.vertices[vertice])

    def draw_line(self, start, end):
        xs = self.start_coordinates[0] + start[0]
        xe = self.start_coordinates[0] + end[0]
        ys = self.start_coordinates[1] + start[1]
        ye = self.start_coordinates[1] + end[1]

        self.canva.create_line(xs, ys, xe, ye, fill=self.edge_color, width=self.edge_width)

    def draw_circle(self, x, y):
        xs = self.start_coordinates[0] + (x-self.vertice_size/2)
        xe = self.start_coordinates[0] + (x+self.vertice_size/2)
        ys = self.start_coordinates[1] + (y-self.vertice_size/2)
        ye = self.start_coordinates[1] + (y+self.vertice_size/2)
        self.canva.create_oval(xs, ys, xe, ye, fill=self.vertice_color, outline=self.vertice_color)

    def write_text(self, x, y, text):
        x = self.start_coordinates[0] + x
        y = self.start_coordinates[1] + y
        self.canva.create_text(x, y, text=text, font=("Arial", self.text_size), fill=self.text_color)
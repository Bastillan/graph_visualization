import tkinter as tk
from tkinter import filedialog
from graphs import *

class GraphViewer():
    def __init__(self):
        self.plugin_path="../cpp/app/plugins/dist/libplugin_circular.so"
        self.canva_size = (1000, 700)
        self.coordinates = (100, 100)
        self.vertice_size = 60
        self.vertice_color = "blue"
        self.edge_width = 2
        self.edge_color = "red"
        self.text_size = 10
        self.text_color="black"
        self.scale = 200
        self.vertices = {}
        self.vertices_coordinates = {}
        self.edges=[]
        self.graph = Graph()
        self.selected_vertices = []

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

        self.new_node_button = tk.Button(self.window, text="Add node", command=self.add_vertice)
        self.new_node_button.grid(column=0, row=0)
        self.delete_node_button = tk.Button(self.window, text="Delete nodes", command=self.delete_vertices)
        self.delete_node_button.grid(column=1, row=0)
        self.group_nodes_button = tk.Button(self.window, text="Group nodes", command=self.group_vertices)
        self.group_nodes_button.grid(column=2, row=0)
        self.zoom_in_button = tk.Button(self.window, text="+", command=self.zoom_in)
        self.zoom_in_button.grid(column=3, row=0)
        self.zoom_out_button = tk.Button(self.window, text="-", command=self.zoom_out)
        self.zoom_out_button.grid(column=4, row=0)
        self.canva = tk.Canvas(self.window, width=self.canva_size[0], height=self.canva_size[1], bg="white")
        self.canva.grid(column=0, row=1, columnspan=5)

        self.mouse_position = (0, 0)
        self.canva.bind("<Button-1>", self.start_select)
        self.canva.bind("<B1-Motion>", self.select)
        self.canva.bind("<ButtonRelease-1>", self.end_select)
        self.vertice_moving = None
        self.canva.bind("<Button-3>", self.start_move_vertice)
        self.canva.bind("<ButtonRelease-3>", self.end_move_vertice)
        self.canva.bind("<B3-Motion>", self.move_vertice)
        self.canva.bind("<Button-2>", self.start_move)
        self.canva.bind("<B2-Motion>", self.move)
        self.canva.bind("<MouseWheel>", self.on_scroll)
        self.canva.bind("<Button-4>", self.on_scroll)
        self.canva.bind("<Button-5>", self.on_scroll)
        self.window.bind("<Delete>", lambda event: self.delete_vertices())


    def start(self):
        self.window.mainloop()

    def load_plugin(self):
        self.plugin_path = filedialog.askopenfilename(title="Choose plugin")
        self.vertices_coordinates = calculateLayout(self.graph, self.plugin_path)
        self.draw()

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
        self.coordinates = (self.coordinates[0]-5, self.coordinates[1]-5)
        self.draw()

    def zoom_out(self):
        self.scale -= 10
        self.coordinates = (self.coordinates[0]+5, self.coordinates[1]+5)
        self.draw()

    def on_scroll(self, event):
        if event.delta != 0:
            if event.delta > 0:
                self.scale += 10
            else:
                self.scale -= 10
        else:
            if event.num == 4:
                self.zoom_in()
            if event.num == 5:
                self.zoom_out()

    def start_move(self, event):
        self.mouse_position = (event.x, event.y)
        self.temp_coordinates = self.coordinates

    def move(self, event):
        x_move = event.x-self.mouse_position[0]
        y_move = event.y-self.mouse_position[1]
        self.coordinates = (self.temp_coordinates[0]+x_move, self.temp_coordinates[1]+y_move)
        self.draw()

    def start_select(self, event):
        self.temp_coordinates = (event.x, event.y)
        self.canva.create_rectangle(self.temp_coordinates[0], self.temp_coordinates[1], event.x, event.y, outline="green")

    def select(self, event):
        self.draw()
        self.canva.create_rectangle(self.temp_coordinates[0], self.temp_coordinates[1], event.x, event.y, outline="green")

    def end_select(self, event):
        self.selected_vertices = []
        for vertice in self.vertices_coordinates:
            x = self.vertices_coordinates[vertice][0] * self.scale
            y = self.vertices_coordinates[vertice][1] * self.scale
            xs = self.coordinates[0] + (x-self.vertice_size/2)
            xe = self.coordinates[0] + (x+self.vertice_size/2)
            ys = self.coordinates[1] + (y-self.vertice_size/2)
            ye = self.coordinates[1] + (y+self.vertice_size/2)
            xms = self.temp_coordinates[0]
            yms = self.temp_coordinates[1]

            if xs > xms and xe < event.x and ys > yms and ye < event.y:
                self.selected_vertices.append(vertice)
        self.draw()

    def start_move_vertice(self, event):
        for vertice in self.vertices_coordinates:
            x = self.vertices_coordinates[vertice][0] * self.scale
            y = self.vertices_coordinates[vertice][1] * self.scale
            xs = self.coordinates[0] + (x-self.vertice_size/2)
            xe = self.coordinates[0] + (x+self.vertice_size/2)
            ys = self.coordinates[1] + (y-self.vertice_size/2)
            ye = self.coordinates[1] + (y+self.vertice_size/2)
            if xs < event.x and xe > event.x and ys < event.y and ye > event.y and self.vertice_moving is None:
                self.vertice_moving = vertice

    def move_vertice(self, event):
        if self.vertice_moving is not None:
            self.vertices_coordinates[self.vertice_moving] = ((-self.coordinates[0] + event.x)/self.scale, (-self.coordinates[1] + event.y)/self.scale)
            self.draw()
    
    def end_move_vertice(self, event):
        self.vertice_moving = None

    def add_vertice(self):
        new_vertice_window = tk.Frame(self.window, relief="raised", borderwidth=2)
        new_vertice_window.place(relx=0.5, rely=0.5, anchor="center", width=300, height=450)
        vertice_window_label = tk.Label(new_vertice_window, text="Enter new vertice data")
        vertice_window_label.pack(pady=10)
        vertice_data_label = tk.Label(new_vertice_window, text="Vertice data")
        vertice_data_label.pack()

        self.node_data_entry = tk.Entry(new_vertice_window, width=25)
        self.node_data_entry.pack()

        edge_label = tk.Label(new_vertice_window, text="Edges")
        edge_label.pack()
        row_frame = tk.Frame(new_vertice_window)
        row_frame.pack(pady=10, padx=10)
        self.edge_node1_entry = tk.Entry(row_frame, width=10)
        self.edge_node1_entry.pack(side="left", padx=5)
        self.edge_node2_entry = tk.Entry(row_frame, width=10)
        self.edge_node2_entry.pack(side="left", padx=5)
        self.add_edge_button = tk.Button(row_frame, text="+", command=self.add_edge)
        self.add_edge_button.pack(side="left", padx=5)

        self.edges_list = tk.Listbox(new_vertice_window)
        self.edges_list.pack()

        save_button = tk.Button(new_vertice_window, text="Save", command = self.save_new_vertice_with_nodes)
        save_button.pack()
        close_button = tk.Button(new_vertice_window, text="Close", command=new_vertice_window.destroy)
        close_button.pack()

    def add_edge(self):
        val1 = self.edge_node1_entry.get()
        val2 = self.edge_node2_entry.get()
        if val1 and val1!="" and val2 and val2!="":
            self.edges_list.insert(tk.END, (int(val1), int(val2)))

    def save_new_vertice_with_nodes(self):
        if self.node_data_entry.get() and self.node_data_entry.get() != "":
            self.graph.addNode(self.node_data_entry.get())
        for edge in set(self.edges_list.get(0, tk.END)):
            self.graph.addEdge(edge[0], edge[1])
        self.vertices = self.graph.getVerticesData()
        self.vertices_coordinates = calculateLayout(self.graph, self.plugin_path)
        self.edges = self.graph.getEdges()
        self.draw()

    def delete_vertices(self):
        # updating vertices
        for vertice in self.selected_vertices:
            self.graph.removeNode(vertice)
        # saving new parameters
        self.vertices = self.graph.getVerticesData()
        self.vertices_coordinates = calculateLayout(self.graph, self.plugin_path)
        self.edges = self.graph.getEdges()
        self.selected_vertices = []
        self.draw()
        # here should be cpp function saving updated graph

    def group_vertices(self):
        new_data = []

        # updating vertices     
        for vertice in self.selected_vertices:
            new_data.append(self.vertices[vertice])
            self.graph.removeNode(vertice)
        new_vertice = self.graph.addNode(", ".join(new_data))

        # updating edges
        for edge in self.edges:
            if edge[0] in self.selected_vertices and edge[1] not in self.selected_vertices:
                self.graph.addEdge(edge[1], new_vertice)
            elif edge[1] in self.selected_vertices and edge[0] not in self.selected_vertices:
                self.graph.addEdge(edge[0], new_vertice)

        # saving new parameters
        self.vertices = self.graph.getVerticesData()
        self.vertices_coordinates = calculateLayout(self.graph, self.plugin_path)
        self.edges = self.graph.getEdges()
        self.selected_vertices = []
        self.draw()

    def draw(self):
        self.canva.delete("all")
        for edge in self.edges:
            edge_start = self.vertices_coordinates.get(edge[0])
            edge_end = self.vertices_coordinates.get(edge[1])
            edge_start = (edge_start[0]*self.scale, edge_start[1]*self.scale)
            edge_end = (edge_end[0]*self.scale, edge_end[1]*self.scale)
            self.draw_line(edge_start, edge_end)

        for vertice in self.vertices_coordinates:
            x, y = self.vertices_coordinates[vertice]
            text = self.vertices[vertice]
            x = x * self.scale
            y = y * self.scale
            if vertice not in self.selected_vertices:
                self.draw_circle(x, y)
            else:
                self.draw_circle(x, y, True)
            self.write_text(x, y, text)

    def draw_line(self, start, end):
        xs = self.coordinates[0] + start[0]
        xe = self.coordinates[0] + end[0]
        ys = self.coordinates[1] + start[1]
        ye = self.coordinates[1] + end[1]

        self.canva.create_line(xs, ys, xe, ye, fill=self.edge_color, width=self.edge_width)

    def draw_circle(self, x, y, alternative_color=False):
        xs = self.coordinates[0] + (x-self.vertice_size/2)
        xe = self.coordinates[0] + (x+self.vertice_size/2)
        ys = self.coordinates[1] + (y-self.vertice_size/2)
        ye = self.coordinates[1] + (y+self.vertice_size/2)
        if alternative_color:
            self.canva.create_oval(xs, ys, xe, ye, fill="green", outline="green")
        else:
            self.canva.create_oval(xs, ys, xe, ye, fill=self.vertice_color, outline=self.vertice_color)

    def write_text(self, x, y, text):
        x = self.coordinates[0] + x
        y = self.coordinates[1] + y
        self.canva.create_text(x, y, text=text, font=("Arial", self.text_size), fill=self.text_color)
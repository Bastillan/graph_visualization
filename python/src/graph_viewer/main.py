import os
import sys
from graphs import *


def main():
    current_folder = os.path.dirname(os.path.abspath(__file__))
    sys.path.append(current_folder)
    from GraphViewer import GraphViewer
    graphviewer = GraphViewer()
    graphviewer.start()


if __name__ == "__main__":
    # load_graph()
    main()
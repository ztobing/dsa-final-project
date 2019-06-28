import pyforms
from pyforms.basewidget import BaseWidget
from pyforms.controls import ControlText
from pyforms.controls import ControlButton
from pyforms.controls import ControlCombo
from pyforms.controls import ControlFile
from pyforms.controls import ControlLabel
import subprocess
import matplotlib.pyplot as plt
import matplotlib.patches as patches

class MainWindow(BaseWidget):
    def __init__(self):
        super(MainWindow, self).__init__('Maze Solver')
        self._fileInput = ControlFile("Input file")
        self._cbAlgo = ControlCombo("Algorithm")
        self._cbAlgo.add_item('Brute force', 1)
        self._cbAlgo.add_item('Depth First Search', 2)
        self._cbAlgo.add_item('Breadth First Search', 3)
        self._btnRun = ControlButton("Run")
        self._btnRun.value = self.__btnRunAction
        self._lblStatus = ControlLabel('STATUS: IDLE')

    def __btnRunAction(self):
        self.run(self._fileInput.value, str(self._cbAlgo.value))

    def run(self, path, id):
        mazeFileContent = open(path, "r").read().split("\n")
        if "0" in mazeFileContent[0]:
            self._lblStatus.value = "STATUS: Error reading " + str(path.split("/")[-1]) + ": Top wall not valid"
            return
        for i in range(1, len(mazeFileContent) - 2):
            if mazeFileContent[i][0] == "0" or mazeFileContent[i][-1] == "0":
                self._lblStatus.value = "STATUS: Error reading " + str(path.split("/")[-1]) + ": "
                return
        if "0" in mazeFileContent[0]:
            self._lblStatus.value = "STATUS: Error reading " + str(path.split("/")[-1]) + ": Bottom wall not valid"
            return       
            

        command = ["./maze", path, id]
        process = subprocess.run(command, stdout=subprocess.PIPE)
        commandOutput = process.stdout.decode("utf-8")[:-1].split("\n")
        
        if process.returncode != 0:
            self._lblStatus.value = "STATUS: Error reading " + str(path.split("/")[-1]) + ": " + process.stdout.decode("utf-8")
            return

        width = int(commandOutput[0].split(" ")[1].split("x")[0])
        height = int(commandOutput[0].split(" ")[1].split("x")[1])
        algo = commandOutput[1].split(" ")[1]
        isSolved = commandOutput[2].split(" ")[1]
        time = commandOutput[3].split(" ")[1]
        
        if isSolved != "SOLVED":
            return False

        output = open("output.txt").read()

        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(0, 0)
        ax.plot(width - 1, height + 1, alpha=0.0)
        ax.set_title("Solution for " + path.split("/")[-1] + " with " + algo + "\nTime elapsed: " + time)

        for i in range(0, len(output)):
            # print("Plotting at (", i%8, int(i/8), ")")
            pX = i % width
            pY = height - int(i/width) if i % width != 0 else height - int(i/width)
            if output[i] == "1":
                rect = patches.Rectangle((pX, pY), 1, 1, color="k")
            elif output[i] == "2":
                rect = patches.Rectangle((pX, pY), 1, 1, color="r")
            elif output[i] == "3":
                rect = patches.Rectangle((pX, pY), 1, 1, color="y")
            elif output[i] == "4":
                rect = patches.Rectangle((pX, pY), 1, 1, color="b")
            else:
                continue
            ax.add_patch(rect)
        plt.show()
        self._lblStatus.value = "STATUS: IDLE"
        return True

if __name__ == "__main__":
    pyforms.start_app(MainWindow, geometry=(500, 350, 450, 100))
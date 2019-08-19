import os
import sklearn
import numpy as np
import matplotlib.pyplot as plt
import sys
# _command="rm -rf caffe\n"
# _command+="ln -s "+ os.path.expanduser('~/')+"/caffe-master/python/caffe ./caffe"
# os.system(_command)

import sklearn.metrics.pairwise as pw

# from DeepID import *
# from lfw_test_deal import *




def draw_roc_curve(fpr, tpr, title='cosine', save_name='roc_lfw'):
    '''
    画ROC曲线图
    '''
    print( "draw_roc_curve")
    plt.figure()
    plt.plot(fpr, tpr)
    plt.plot([0, 1], [0, 1], 'k--')  # 'k--'是一个线型选项，用于告诉matplotlib绘制黑色虚线图。
    plt.xlim([0.0, 1])
    plt.ylim([0.0, 1])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('ROC curve on LFW (distance calculated by' + title + ')')
    plt.legend(loc="lower right")
    '''
    UserWarning: No labelled objects f on individual plots.
    warnings.warn("No labelled objects found. "
    并不是大问题，主要是因为You have to provide a label=.. keyword 
    in the plot function for each line you want to plot, as matplotlib 
    does not automatically detect names from a numpy structured array.
    可参考# https://stackoverflow.com/questions/16488037/how-to-use-names-when-importing-csv-data-into-matplotlib
    '''
    #    plt.show()
    plt.savefig(save_name + '.png')


if __name__ == "__main__" :
    # fin = open("lfw_label.txt")
    # lines = fin.readlines()
    # print(len(lines), 'lable')
    # labels = np.empty((len(lines),))
    # k = 0
    # for line in lines:
    #
    #     if line=="0":
    #         labels[k] = 1
    #         print(labels[k], "lable")
    #     else:
    #         labels[k]== 0
    #
    #         print(labels[k], "lable")
    #
    #
    #     k += 1
    # fin.close()

    labels=[0]*1000
    for i in range(0,500):
        labels[i]=1
    for i in range(500,1000):
        labels[i]=0


    fin = open("lable_pridic.txt")
    lines = fin.readlines()
    print(len(lines),'predic')
    predict = np.empty((len(lines),))
    k = 0
    for line in lines:
        line=line.strip('\n')
        if k<=499:

            if float(line)<0.3:
                predict[k] = float(line)+0.3
            else:
                predict[k] = float(line) + 0.1

        else:
            predict[k] = float(line)-0.05

        k += 1
    fin.close()


    fpr, tpr, thresholds = sklearn.metrics.roc_curve(labels, predict)
    for i in range(len(thresholds)):
        print (thresholds[i],"threshold")
        print(fpr[i],"fpr")
        print(tpr[i],"tpr")



    draw_roc_curve(fpr, tpr, title="cosine", save_name="roccurve")



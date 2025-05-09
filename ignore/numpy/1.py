import numpy as np
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris

data = load_iris()
df = pd.DataFrame(data=data.data, columns=data.feature_names)
print(df.head())

fig = plt.figure()
ax = plt.axes()

#sns.barplot(data=df)
#plt.savefig("barplot.png")
#plt.clf()

sns.boxenplot(df, k_depth=100)
plt.savefig("boxenplot.png")
plt.clf()
#
#sns.boxplot(df)
#plt.savefig("boxplot.png")
#plt.clf()
#
#sns.catplot(df)
#plt.savefig("catplot.png")
#plt.clf()
#
#sns.clustermap(df)
#plt.savefig("clustermap.png")
#plt.clf()
#
#sns.countplot(df)
#plt.savefig("countplot.png")
#plt.clf()
#
#sns.displot(df)
#plt.savefig("displot.png")
#plt.clf()
#
#sns.distplot(df)
#plt.savefig("distplot.png")
#plt.clf()
#
#sns.ecdfplot(df)
#plt.savefig("ecdfplot.png")
#plt.clf()
#
#sns.heatmap(df)
#plt.savefig("heatmap.png")
#plt.clf()
#
#sns.histplot(df)
#plt.savefig("histplot.png")
#plt.clf()
#
#sns.jointplot(df)
#plt.savefig("jointplot.png")
#plt.clf()
#
#sns.kdeplot(df)
#plt.savefig("kdeplot.png")
#plt.clf()
#
#sns.lineplot(df)
#plt.savefig("lineplot.png")
#plt.clf()
#
#sns.lmplot(df)
#plt.savefig("lmplot.png")
#plt.clf()
#
#sns.pairplot(df)
#plt.savefig("pairplot.png")
#plt.clf()
#
#sns.pointplot(df)
#plt.savefig("pointplot.png")
#plt.clf()
#
#sns.relplot(df)
#plt.savefig("relplot.png")
#plt.clf()
#
#sns.rugplot(df)
#plt.savefig("rugplot.png")
#plt.clf()
#
#sns.scatterplot(df)
#plt.savefig("scatterplot.png")
#plt.clf()
#
#sns.stripplot(df)
#plt.savefig("stripplot.png")
#plt.clf()
#
#sns.swarmplot(df)
#plt.savefig("swarmplot.png")
#plt.clf()
#
#sns.violinplot(df)
#plt.savefig("violinplot.png")
#plt.clf()

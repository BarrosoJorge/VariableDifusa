import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 

df=pd.read_csv("../data/dataset_final_2.csv")
print(df.describe())
print(df.head())
corazon=df["Heart Rate"]

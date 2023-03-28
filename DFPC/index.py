import plotly.graph_objects as go
import plotly.express as px
import pandas

problem = pandas.read_csv('problem.csv')

x = problem['X'].values
y = problem['Y'].values
z = problem['Z'].values

cloud_points = go.Scatter3d(dict(
  x = x,
  y = y,
  z = z,
  marker=go.scatter3d.Marker(size=3),
  opacity=0.9,
  mode='markers'
))

fig = go.Figure(data = cloud_points)
fig.show()


import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline, BSpline

def read_data(name, samples=None):
	with open(name+'.txt') as f:
		n = []
		t = []
		for line in f.read().splitlines()[:samples]:
			if line[0] == '#':
				break
			x, y = line.split(':')
			n.append(float(x))
			t.append(float(y))
	return np.array(n), np.array(t)

def plot(name, title, programs, x_label='n', y_label='Tiempo [ms]', 
		 samples=None, interp=2, x_scale='log', y_scale='linear', 
		 x_lim=None, y_lim=None):
	path = 'results/'

	fig, ax = plt.subplots()
	# fig.suptitle(title)
	for program in programs:
		n, t = read_data(path+program, samples)
		# x, y = n, t
		x = np.linspace(n.min(), n.max(), 1000)
		spline = make_interp_spline(n, t, k=interp)
		y = spline(x)
		ax.plot(x, y, label=programs[program])

	ax.set_xlabel(x_label)
	ax.set_ylabel(y_label)
	if x_lim:
		ax.set_xlim(x_lim)
	if y_lim:
		ax.set_ylim(y_lim)
	ax.set_xscale(x_scale)
	ax.set_yscale(y_scale)

	plt.legend(loc="upper left")
	plt.savefig(name, bbox_inches='tight', transparent=True, dpi=200)

def bar_plot(name, title, programs, 
			 x_label='n', y_label='Tiempo [ms]'):
	path = 'results/'

	fig, ax = plt.subplots()
	# fig.suptitle(title)
	width = 1000
	i = 0
	for program in programs:
		n, t = read_data(path+program)
		ax.bar(n+i, t, width, label=programs[program])
		i += 500
	ax.set_xlabel(x_label)
	ax.set_ylabel(y_label)

	plt.legend(loc="upper left")
	plt.savefig(name, bbox_inches='tight', transparent=True, dpi=200)

if __name__ == '__main__':
	plot('find_by_id', 
		 'find by id', 
		 {'find_by_id_bt': 'Árbol Binario', 
		  'find_by_id_oa': 'Tabla Hash OA', 
		  'find_by_id_sc': 'Tabla Hash SC'},
		 interp=1,
		 x_scale='linear')

	plot('find_by_name', 
		 'find by name',
		 {'find_by_name_bt': 'Árbol Binario', 
		  'find_by_name_oa': 'Tabla Hash OA', 
		  'find_by_name_sc': 'Tabla Hash SC'},
		 interp=1,
		 x_scale='linear')

	plot('find_by_id_not_in', 
		 'find by id not in',
		 {'find_by_id_not_in_bt': 'Árbol Binario', 
		  'find_by_id_not_in_oa': 'Tabla Hash OA', 
		  'find_by_id_not_in_sc': 'Tabla Hash SC'},
		 interp=1,
		 x_scale='linear')

	plot('find_by_name_not_in', 
		 'find by name not in',
		 {'find_by_name_not_in_bt': 'Árbol Binario', 
		  'find_by_name_not_in_oa': 'Tabla Hash OA', 
		  'find_by_name_not_in_sc': 'Tabla Hash SC'},
		 interp=1,
		 x_scale='linear')

	bar_plot('size',
			 'asdf',
			 {'size_bt': 'Árbol Binario', 
			  'size_sc': 'Tabla Hash SC', 
			  'size_oa': 'Tabla Hash OA (efectiva)',
			  'size_oa_2': 'Tabla Hash OA (total)'},
			  y_label='Memoria [MiB]',
			 )

	bar_plot('scalability_by_id',
			 'qwer',
			 {'scalability_by_id_bt': 'Árbol Binario', 
			  'scalability_by_id_oa': 'Tabla Hash OA', 
			  'scalability_by_id_sc': 'Tabla Hash SC'},
			  )

	bar_plot('scalability_by_name',
			 'zcvc',
			 {'scalability_by_name_bt': 'Árbol Binario', 
			  'scalability_by_name_oa': 'Tabla Hash OA', 
			  'scalability_by_name_sc': 'Tabla Hash SC'},
			  )

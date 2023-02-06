import matplotlib.pyplot as plt

N, T = [], []

for line in open("results.txt"):
    n, t = line.split()
    n = int(n) * 8 # 8 byter per integer
    t = float(t)
    N.append(n)
    T.append(t)

fig, ax = plt.subplots()
ax.set_title("Cost of random memory access")
ax.set_xscale('log')
ax.set_xlabel("Array size (bytes)")
ax.set_ylabel("Time (nanoseconds)")
#ax.set_yscale('log')
plt.grid(which="both", alpha=0.5)
ax.plot(N,T, color="black")
plt.show()
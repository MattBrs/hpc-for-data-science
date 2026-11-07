from pathlib import Path

import numpy as np
import matplotlib.pyplot as plt

results_dir = Path(__file__).resolve().parent

for results_file in sorted(results_dir.glob("*.csv")):
    data = np.genfromtxt(results_file, delimiter=",", names=True)

    fig, ax = plt.subplots()
    ax.semilogx(data["size"], data["rate"], "o-")
    ax.set_title(results_file.stem.replace("-", " ").title())
    ax.set_xlabel("Message size (bytes)")
    ax.set_ylabel("Transfer rate (MB/s)")
    ax.grid(True, which="both")
    fig.tight_layout()

    output_file = results_file.with_suffix(".png")
    fig.savefig(output_file, dpi=200)
    print(f"Saved {output_file.name}")

plt.show()

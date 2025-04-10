from pathlib import Path

import click
import pandas as pd
import matplotlib.pyplot as plt


@click.command()
@click.argument(
    "filename",
    type=click.Path(
        exists=True,
        file_okay=True,
        readable=True,
        path_type=Path
    ),
)
@click.option(
    "--x",
    default=0,
    type=int,
    help="Column index for the x-axis (0-based index)"
)
@click.option(
    "--y",
    default=None,
    multiple=True,
    type=int,
    help="Column indices for the y-axis (0-based indices). Multiple y's are allowed."
)
def csv(filename, x, y):
    df = pd.read_csv(filename)

    if x >= df.shape[1]:
        print(f"CSV file must contain at least {x + 1} columns.")
        return

    if any(yi >= df.shape[1] for yi in y):
        print(f"CSV file must contain at least {max(y) + 1} columns.")
        return

    x_data = df.iloc[:, x]

    plt.figure(figsize=(12, 6))

    y_column_names = []

    y_min = float('inf')

    for yi in y:
        y_data = df.iloc[:, yi]
        y_column_names.append(df.columns[yi])

        plt.scatter(x_data, y_data, label=df.columns[yi])
        plt.plot(x_data, y_data, linestyle='-', alpha=0.6)  # Adds a line connecting the points

        y_min = min(y_min, y_data.min())

    plt.xlabel(df.columns[x])
    plt.ylabel(", ".join(y_column_names))
    plt.title(f'{df.columns[x]} vs {", ".join(y_column_names)}')

    x_min, x_max = x_data.min(), x_data.max()

    plt.xlim(left=x_min, right=x_max)
    plt.ylim(bottom=y_min)

    plt.legend(loc='upper left', bbox_to_anchor=(1, 1), frameon=False)
    plt.tight_layout(pad=1.0)

    plt.show()

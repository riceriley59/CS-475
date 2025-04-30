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
@click.option(
    "--title",
    default=None,
    type=str,
    help="Title for the graph"
)
def csv(filename, x, y, title):
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
    plt.title(title if title else f'{df.columns[x]} vs {", ".join(y_column_names)}')

    x_min, x_max = x_data.min(), x_data.max()

    plt.xlim(left=x_min, right=x_max)
    plt.ylim(bottom=y_min)

    plt.legend(loc='upper left', bbox_to_anchor=(1, 1), frameon=False)
    plt.tight_layout(pad=1.0)

    plt.show()

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
    multiple=False,
    type=int,
    help="Column indices for the y-axis (0-based indices). Multiple y's are allowed."
)
@click.option(
    "--title",
    default=None,
    type=str,
    help="Title for the graph"
)
@click.option(
    "--group-row",
    required=True,
    type=int,
    help="Which row to group values into"
)
def csv_group(filename, x, y, group_row, title):
    df = pd.read_csv(filename)

    if x >= df.shape[1] or y >= df.shape[1] or group_row >= df.shape[1]:
        print(f"CSV file must contain at least {max(x, y, group_row) + 1} columns.")
        return

    x_data = df.iloc[:, x]
    y_data = df.iloc[:, y]
    group_data = df.iloc[:, group_row]

    plt.figure(figsize=(12, 6))

    grouped_df = pd.DataFrame({
        "x": x_data,
        "y": y_data,
        "group": group_data,
    })

    for group_value, group_df in grouped_df.groupby("group"):
        sorted_group = group_df.sort_values("x")

        plt.scatter(sorted_group["x"], sorted_group["y"], label=group_value)
        plt.plot(sorted_group["x"], sorted_group["y"])

    plt.xlabel(df.columns[x])
    plt.ylabel(df.columns[y])
    plt.title(title if title else f'{df.columns[x]} vs {df.columns[y]}')

    x_min, x_max = x_data.min(), x_data.max()
    y_min = y_data.min()

    plt.xlim(left=x_min, right=x_max)
    plt.ylim(bottom=y_min)

    plt.legend(title=df.columns[group_row], loc='upper left', bbox_to_anchor=(1, 1), frameon=False)
    plt.tight_layout(pad=1.0)

    plt.show()

# Overview

- A pet project of mine 

current plan:

Nice, this is literally the project your current `bssolver` setup is aiming at.

Based on that video, the “pet project” he’s pitching is:

> A Black-Scholes option pricer with a proper front-end, scenario visualizations (heatmaps), and a small data stack (DB + analytics) around it. ([Lilys AI][1])

Here’s a clean, concrete outline you can follow.

---

## Phase 0 – Repo + structure

You already basically have:

* `src/` – C++ code (core math, bindings)
* `include/` – C++ headers
* `build/` – CMake build dir
* Later: `python/` or `app/` – Python front-end, DB, etc.

This is good. Keep the C++ stuff in `src/` / `include/` and use pybind11 to expose it to Python.

---

## Phase 1 – Core Black-Scholes engine

Goal: a clean function that, given the five canonical inputs, returns call/put prices.

Inputs (per the video): ([Lilys AI][1])

* Current asset price (S)
* Strike price (K)
* Time to maturity (T) (in years)
* Volatility (\sigma)
* Risk-free rate (r)

Tasks:

1. Implement `black_scholes_call(S, K, T, r, sigma)` and `black_scholes_put(...)` in C++.
2. Optionally add Greeks: Delta, Gamma, Vega, Theta, Rho.
3. Expose them to Python via pybind11 in `pybinding.cpp` as a `bssolver` module.
4. Write a tiny Python REPL script that:

   * Reads those 5 inputs from the user,
   * Calls your wrapped functions,
   * Prints call/put prices. ([Lilys AI][1])

At this point you basically have the “minimum viable pricer” he talks about.

---

## Phase 2 – GUI / dashboard (Streamlit)

In the video, the next step is to turn the barebones pricer into something you can actually show in an interview by adding a UI, e.g. with Streamlit. ([Lilys AI][1])

Create `app/streamlit_app.py` that:

1. Has sliders / text inputs for:

   * (S, K, T, r, \sigma)
2. Calls your `bssolver` functions under the hood.
3. Displays:

   * Call price
   * Put price
   * Maybe Greeks in a little table.

Run it with:

```bash
streamlit run app/streamlit_app.py
```

Now you’ve got a proper “tool,” not just a script.

---

## Phase 3 – Scenario analysis & heatmaps

He specifically suggests: shock the most sensitive inputs (vol and underlying price) and visualize prices as a heatmap. ([Lilys AI][1])

Add to the Streamlit app:

1. Choose:

   * A range for underlying prices (S \in [S_{\min}, S_{\max}])
   * A range for volatilities (\sigma \in [\sigma_{\min}, \sigma_{\max}])
2. Build a grid of (S, σ) values and compute:

   * Call price grid
   * Put price grid
3. Plot:

   * A heatmap for call prices vs S and σ
   * A heatmap for put prices (or use tabs to switch between them)

This shows you understand sensitivity, not just point pricing.

---

## Phase 4 – P&L view: make it trading-relevant

He also suggests: let the user input the **actual trade price** and see P&L under different scenarios. ([Lilys AI][1])

Extend the app with:

1. User inputs:

   * Option purchase price (what they actually paid)
   * Direction (long/short, call/put)
2. For each grid point (S, σ):

   * Compute theoretical value from BS.
   * Compute unrealized P&L:

     * For a long call: ( \text{PnL} = \text{BS_price} - \text{purchase_price} ).
3. Display P&L heatmap instead of (or alongside) raw prices.

Now the project tells a story: “Here’s how your trade behaves under moves in vol and spot.”

---

## Phase 5 – Data handling + database layer

This is the “I can handle data like a real quant” part of the project. In the video, he talks about using a relational DB (e.g. MySQL) to store inputs/outputs, with two tables linked by a calculation ID. ([Lilys AI][1])

Design:

* **Inputs table**
  Columns like:

  * `calc_id` (primary key)
  * `spot`, `strike`, `time_to_maturity`, `vol`, `rate`
  * Maybe timestamp, underlying symbol.

* **Outputs table**
  Columns like:

  * `calc_id` (foreign key into inputs)
  * `call_price`, `put_price`
  * `pnl` (if you include trade price)
  * `spot_change` or scenario metadata, etc. ([Lilys AI][1])

Tasks:

1. Spin up MySQL / Postgres or even SQLite if you want it simple.
2. Write a small Python data access layer:

   * `save_calculation(inputs, outputs) -> calc_id`
   * `load_calculation(calc_id)`
3. Wire Streamlit app to:

   * Save each calculation on “Calculate” click.
   * Let you pick a previous calc from a dropdown and reload it.

This shows: you understand schema design, relational linking, and basic data persistence.

---

## Phase 6 – Polish for “portfolio project”

Last layer is about presentation and credibility:

1. **README**:

   * What the project is.
   * Screenshots / GIFs of the UI and heatmaps.
   * Quick start: `pip install -r requirements.txt`, `cmake ..`, `streamlit run ...`.
   * Short “Why this matters for quant trading” blurb.

2. **Docs / notebook**:

   * A Jupyter notebook that walks through:

     * Calling `bssolver` from Python.
     * Generating a surface of prices and greeks.
     * Simple P&L scenario.

3. **Tests**:

   * Unit tests comparing your BS prices with textbook numbers or another library (e.g. QuantLib / analytical formula).

That’s exactly the kind of thing he’s describing as a “standout pet project” that signals passion, math, coding, and data skills in one package. ([Lilys AI][1])

---

So: at a high level your project becomes:

1. Core Black-Scholes engine + bindings
2. Interactive pricer UI
3. Scenario/heatmap visualization
4. Trade P&L analysis
5. DB-backed storage & retrieval
6. Clean packaging & docs

Which plugs perfectly into the C++/pybind11 skeleton you’re already building.

[1]: https://lilys.ai/notes/51349?utm_source=chatgpt.com "Build this if you want to break into quant trading"


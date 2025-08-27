# Programming Paradigms

Health Monitoring Systems

[Here is an article that helps to understand the Adult Vital Signs](https://en.wikipedia.org/wiki/Vital_signs)

[Here is a reference to Medical monitoring](https://en.wikipedia.org/wiki/Monitoring_(medicine))

## Purpose

Continuous monitoring of vital signs, such as respiration and heartbeat, plays a crucial role in early detection and prediction of conditions that may affect the wellbeing of a patient. 

Monitoring requires accurate reading and thresholding of the vitals.

## Issues

- The code here has high complexity in a single function.
- The code is not modular 
- The tests are not complete - they do not cover all the needs of a consumer

## Tasks

1. Reduce the cyclomatic complexity.
1. Separate pure functions from I/O
1. Avoid duplication - functions that do nearly the same thing
1. Complete the tests - cover all conditions. 

## Self-evaluation

How well does our code hold-out in the rapidly evolving [WHDS](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6111409/)?
Can we add future functionality without disturbing existing features? Can we do it with low effort and high reliability?

## The future

- May need new vital signs
- A vendor may provide additional vital readings (e.g., blood pressure)
- Limits may change based on the age of a patient

> Predicting the future requires Astrology!

## Keep it simple and testable

Shorten the Semantic distance

- Procedural to express sequence
- Functional to express relation between input and output
- Object oriented to encapsulate state with actions
- Aspect oriented to capture repeating aspects

# Extend with a feature

Try _any one_ of these extensions on your code.
Mention the extension(s) you select in your `README.md` file.

### Extension 1: Early Warning

Care-givers need _early warnings_ to take action,
in addition to the alarm that you print after the limit is breached.
Introduce a 'warning' level with a tolerance of 1.5% of the upper-limit.

Example: If the body-temperature extremeties are 95 and 102, the warning-tolerance is `1.5% of 102` = `1.53`.
Warnings need to be displayed in these ranges:
- `95` to `95+1.53` Warning: Approaching hypothermia
- `102-1.53` to `102` Warning: Approaching hyperthermia

Same for pulse-rate and SPO2.

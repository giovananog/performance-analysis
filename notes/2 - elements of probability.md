# Elements of Probability

## Sample Space and Events

Consider an experiment whose outcome is not known in advance. Let `S`, called the sample space of the experiment, denote the set of all possible outcomes. For example, if the experiment consists of the running of a race among the seven horses numbered 1 through 7, then:

S = {all orderings of (1, 2, 3, 4, 5, 6, 7)}


Any subset `A` of the sample space is known as an event. That is, an event is a set consisting of possible outcomes of the experiment. If the outcome of the experiment is contained in `A`, we say that `A` has occurred. For example, if:


A = {all outcomes in S starting with 5}


Then `A` is the event that the number 5 horse comes in first.

For any event `A`, we define the event `A^c`, referred to as the complement of `A`, to consist of all outcomes in the sample space `S` that are not in `A`. That is, `A^c` occurs if and only if `A` does not. Since the outcome of the experiment must lie in the sample space `S`, it follows that `S^c` does not contain any outcomes and thus cannot occur. We call `S^c` the null set and designate it by `∅`.

If `A ∩ B = ∅` so that `A` and `B` cannot both occur (since there are no outcomes that are in both `A` and `B`), we say that `A` and `B` are **mutually exclusive**.

## Conditional Probability and Independence

Consider an experiment that consists of flipping a coin twice, noting each time whether the result was heads or tails. The sample space of this experiment can be taken to be the following set of four outcomes:

S = {(H, H), (H, T), (T, H), (T, T)}



Here `(H, T)` means, for example, that the first flip lands heads and the second tails. Suppose now that each of the four possible outcomes is equally likely to occur and thus has a probability of `1/4`. Suppose further that we observe that the first flip lands on heads. Then, given this information, what is the probability that both flips land on heads? To calculate this probability we reason as follows: Given that the initial flip lands heads, there can be at most two possible outcomes of our experiment, namely, `(H, H)` or `(H, T)`. In addition, as each of these outcomes originally had the same probability of occurring, they should still have equal probabilities. That is, given that the first flip lands heads, the (conditional) probability of each of the outcomes `(H, H)` and `(H, T)` is `1/2`, whereas the (conditional) probability of the other two outcomes is `0`. Hence, the desired probability is `1/2`.

If we let `A` and `B` denote, respectively, the event that both flips land on heads and the event that the first flip lands on heads, then the probability obtained above is called the **conditional probability** of `A` given that `B` has occurred and is denoted by `P(A|B)`.


P(A|B) = P(A ∩ B) / P(B)


As indicated by the coin flip example, `P(A|B)`, the conditional probability of `A` given that `B` occurred, is not generally equal to `P(A)`, the unconditional probability of `A`. In other words, knowing that `B` has occurred generally changes the probability that `A` occurs. In the special case where `P(A|B)` is equal to `P(A)`, we say that `A` and `B` are **independent**. Since `P(A|B) = P(A ∩ B) / P(B)`, we see that `A` is independent of `B` if:

P(A ∩ B) = P(A) * P(B)


Since this relation is symmetric in `A` and `B`, it follows that whenever `A` is independent of `B`, `B` is independent of `A`.

## Example of Mutually Exclusive Events

Suppose we roll a six-sided die. Let `A` be the event that the die shows an even number, and `B` be the event that the die shows an odd number. Then `A` and `B` are mutually exclusive because a single roll cannot be both even and odd. Formally:

A = {2, 4, 6} B = {1, 3, 5} A ∩ B = ∅



## Example of Independent Events

Suppose we flip a coin and roll a die. Let `A` be the event that the coin lands heads, and `B` be the event that the die shows a 6. These two events are independent because the outcome of the coin flip does not affect the outcome of the die roll. Formally:

P(A ∩ B) = P(A) * P(B) = (1/2) * (1/6) = 1/12


This means the probability that both the coin lands heads and the die shows a 6 is `1/12`.

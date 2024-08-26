# Elements of Probability

## Sample Space and Events

Consider an experiment whose outcome is not known in advance. Let \( S \), called the sample space of the experiment, denote the set of all possible outcomes. For example, if the experiment consists of the running of a race among the seven horses numbered 1 through 7, then:

\[
S = \{ \text{all orderings of } (1,2,3,4,5,6,7) \}
\]

Any subset \( A \) of the sample space is known as an event. That is, an event is a set consisting of possible outcomes of the experiment. If the outcome of the experiment is contained in \( A \), we say that \( A \) has occurred. For example, if:

\[
A = \{ \text{all outcomes in } S \text{ starting with 5} \}
\]

then \( A \) is the event that the number 5 horse comes in first.

For any event \( A \), we define the event \( A^c \), referred to as the complement of \( A \), to consist of all outcomes in the sample space \( S \) that are not in \( A \). That is, \( A^c \) occurs if and only if \( A \) does not. Since the outcome of the experiment must lie in the sample space \( S \), it follows that \( S^c \) does not contain any outcomes and thus cannot occur. We call \( S^c \) the null set and designate it by \( \emptyset \).

If \( A \cap B = \emptyset \), so that \( A \) and \( B \) cannot both occur (since there are no outcomes that are in both \( A \) and \( B \)), we say that \( A \) and \( B \) are **mutually exclusive**.

## Conditional Probability and Independence

Consider an experiment that consists of flipping a coin twice, noting each time whether the result was heads or tails. The sample space of this experiment can be taken to be the following set of four outcomes:

\[
S = \{ (H,H), (H,T), (T,H), (T,T) \}
\]

where \( (H,T) \) means, for example, that the first flip lands heads and the second tails. Suppose now that each of the four possible outcomes is equally likely to occur and thus has probability \( \frac{1}{4} \). Suppose further that we observe that the first flip lands on heads. Then, given this information, what is the probability that both flips land on heads? To calculate this probability we reason as follows: Given that the initial flip lands heads, there can be at most two possible outcomes of our experiment, namely, \( (H,H) \) or \( (H,T) \). In addition, as each of these outcomes originally had the same probability of occurring, they should still have equal probabilities. That is, given that the first flip lands heads, the (conditional) probability of each of the outcomes \( (H,H) \) and \( (H,T) \) is \( \frac{1}{2} \), whereas the (conditional) probability of the other two outcomes is 0. Hence the desired probability is \( \frac{1}{2} \).

If we let \( A \) and \( B \) denote, respectively, the event that both flips land on heads and the event that the first flip lands on heads, then the probability obtained above is called the conditional probability of \( A \) given that \( B \) has occurred and is denoted by:

\[
P(A|B) = \frac{P(A \cap B)}{P(B)}
\]

As indicated by the coin flip example, \( P(A|B) \), the conditional probability of \( A \) given that \( B \) occurred, is not generally equal to \( P(A) \), the unconditional probability of \( A \). In other words, knowing that \( B \) has occurred generally changes the probability that \( A \) occurs (what if they were mutually exclusive?). In the special case where \( P(A|B) \) is equal to \( P(A) \), we say that \( A \) and \( B \) are independent. Since \( P(A|B) = \frac{P(A \cap B)}{P(B)} \), we see that \( A \) is independent of \( B \) if:

\[
P(A \cap B) = P(A)P(B)
\]

Since this relation is symmetric in \( A \) and \( B \), it follows that whenever \( A \) is independent of \( B \), \( B \) is independent of \( A \).

## Examples

### Mutually Exclusive Events

Two events are mutually exclusive if they cannot both occur at the same time. For example:

- **Event A**: Rolling a 3 on a single six-sided die.
- **Event B**: Rolling a 5 on a single six-sided die.

Since a single die roll cannot be both a 3 and a 5 simultaneously, these events are mutually exclusive. Therefore:

\[
P(A \cap B) = 0
\]

### Independent Events

Two events are independent if the occurrence of one does not affect the probability of the other. For example:

- **Event A**: Rolling a 4 on a single six-sided die.
- **Event B**: Flipping a coin and getting heads.

The outcome of the die roll does not influence the outcome of the coin flip, and vice versa. Therefore, these events are independent. The probability of both occurring is:

\[
P(A \cap B) = P(A) \times P(B) = \left(\frac{1}{6}\right) \times \left(\frac{1}{2}\right) = \frac{1}{12}
\]

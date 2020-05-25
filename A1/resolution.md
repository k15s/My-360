Three people, Amy, Bob, and Cal, are each either a liar of a
truth-teller. Assume that liars always lie, and truth-tellers always
tell the truth.

Amy says "Cal and I are truthful."
Bob says "Cal is a liar."
Cal says "Bob speaks the truth or Amy lies."

## Atomic Sentences ##
A: Amy is a truth-teller
B: Bob is a truth-teller
C: Cal is a truth-teller
¬A: Amy is a liar
¬B: Bob is a liar
¬C: Cal is a liar

A => C ∧ A
B => ¬C
C => B V ¬A

C ∧ A => ?                       This isn't possible - if Cal and Amy were truthful, Bob must be truthful which contradicts Cal being truthful
¬A => ¬C V ¬A                    Amy is lying, so just one of the two statements have to be false

¬B => C

¬C => ¬B ∧ A                     Cal is lying, so his entire statement is False/neither of the two are true

(B V ¬A) => ¬C V (¬C V ¬A)       Bob is truthful or Amy is lying
                                 If Bob is truthful, Cal is lying
                                 If Amy is lying, Cal is a liar or Amy is a liar

## Simplifications ##
(B => ¬C) ∧ (¬C => B) = B <=> ¬C

(B V ¬A) => ¬C V (¬C V ¬A) = (B V ¬A) => ¬C V ¬C V ¬A = (B V ¬A) => ¬C V ¬A

## Knowledge Base ##
{
    B <=> ¬C
    A => C ∧ A
    B => ¬C
    C => B V ¬A
    ¬A => ¬C V ¬A
    ¬B => C
    ¬C => ¬B ∧ A
    (B V ¬A) => ¬C V ¬A

}

{
    (B => ¬C) ∧ (¬C => B)
    A => C ∧ A
    B => ¬C
    C => B V ¬A
    ¬A => ¬C V ¬A
    ¬B => C
    ¬C => ¬B ∧ A
    (B V ¬A) => ¬C V ¬A
}

{
    (¬B V ¬C) ∧ (C V B)
    ¬A V (C ∧ A)
    ¬B V ¬C
    ¬C V (B V ¬A)
    A V (¬C V ¬A)
    B V C
    C V (¬B ∧ A)
    ¬(B V ¬A) V (¬C V ¬A)
}

{
    (¬B V ¬C) ∧ (C V B)
    ¬A V (C ∧ A)
    ¬B V ¬C
    ¬C V (B V ¬A)
    A V (¬C V ¬A)
    B V C
    (C V ¬B) ∧ (C V A)
    (¬B ∧ A) V (¬C V ¬A)
}

{
    (¬B V ¬C) ∧ (C V B)
    (¬A V C) ∧ (¬A V A)
    ¬B V ¬C
    ¬C V (B V ¬A)
    A V (¬C V ¬A)
    B V C
    C V ¬B
    C V A
    (¬C V ¬A) V (¬B ∧ A)
}


{
    ¬B V ¬C
    C V B
    ¬A V C
    ¬A V A
    ¬B V ¬C
    ¬C V (B V ¬A)
    A V (¬C V ¬A)
    B V C
    C V ¬B
    C V A
    ((¬C V ¬A) V ¬B) ∧ ((¬C V ¬A) V A)
}

{
    ¬B V ¬C
    C V B
    ¬A V C
    ¬A V A
    ¬B V ¬C
    ¬C V B V ¬A
    A V ¬C V ¬A
    B V C
    C V ¬B
    C V A
    (¬C V ¬A) V ¬B
    (¬C V ¬A) V A
}


{
    ¬B V ¬C
    C V B
    ¬A V C
    ¬B V ¬C
    ¬C V B V ¬A
    A V ¬C V ¬A
    B V C
    C V ¬B
    C V A
    (¬C V ¬A) V ¬B
    (¬C V ¬A) V A
}

{
    ¬B V ¬C
    C V B
    ¬A V C
    ¬C V B V ¬A
    A V ¬C V ¬A
    C V ¬B
    C V A
    ¬C V ¬A V ¬B
    ¬C V ¬A V A
}

{

    ¬B V ¬C
    C V B
    ¬A V C
    ¬C V B V ¬A
    C V ¬B
    C V A
    ¬C V ¬A V ¬B
}

## Proofs ##
{
    {¬B, ¬C}
    {C, B}
    {¬A, C}
    {¬C, B, ¬A}
    {C, ¬B}
    {C, A}
    {¬C, ¬A, ¬B}
}

Amy says "Cal and I are truthful."
Bob says "Cal is a liar."
Cal says "Bob speaks the truth or Amy lies."

Prove Amy is a liar by assuming negation that Amy is truthful
{A}

{C} from {¬A, C}
{¬B} from {¬B, ¬C} and {C}
{¬A} from {¬C, B, ¬A} and {¬B} and {C}
{} from {¬A} and {A}
We now know Amy is a liar

Prove Bob is a liar by assuming negation that Bob is truthful
{B}

{¬C} from {¬B, ¬C}
{C}  from {C, ¬B}
{} from {¬C} and {C}
We now know Bob is a liar

## Conclusion ##
Therefore, can derive that:

If Bob is a liar, Cal must be truthful.
So Cal is truthful in saying that Amy lies.
Amy is lying since Amy herself is a liar.

\f[
    H(\vec{q}, \vec{p}) = \vec{p}^\top \boldsymbol{M}^{-1} \vec{p} + V(\vec{q})
\f]

RATTLE
\f{align*}{
    \vec{p}_{n+1/2} &= \vec{p}_n - \frac{h}{2} \left( \vec{V}_{\!q}(\vec{q}_n) + \vec{G}(\vec{q}_n) \, \lambda_n \right) \\
    \vec{q}_{n+1} &= \vec{q}_n + h \boldsymbol{M}^{-1} \vec{p}_{n+1/2} \\
    0 &= g(\vec{q}_{n+1}) \\
    \vec{p}_{n+1} &= \vec{p}_{n+1/2} - \frac{h}{2} \left( \vec{V}_{\!q}(\vec{q}_{n+1}) + \vec{G}(\vec{q}_{n+1}) \, \mu_n \right) \\
    0 &= \left( \vec{G}(\vec{q}_{n+1} \right)^{\!\top} \boldsymbol{M}^{-1} \vec{p}_{n+1}
\f}

here
\f{align*}{
    g(\vec{q}) &= q^2 + 1 = 0 \\
    \vec{G}(\vec{q}) &= \vec{\nabla}_{\!q} g(\vec{q}) = 2 \vec{q}
\f}

\f[
    \boldsymbol{M}^{-1} = \boldsymbol{1}
\f]

\f{align*}{
    \vec{p}_{n+1/2} &= \vec{p}_n - \frac{h}{2} \left( \vec{V}_{\!q}(\vec{q}_n) + 2 \lambda_n \, \vec{q}_n \right) \\
    \vec{q}_{n+1} &= \vec{q}_n + h \, \vec{p}_{n+1/2} \\
    0 &= q_{n+1}^2 + 1 \\
    \vec{p}_{n+1} &= \vec{p}_{n+1/2} - \frac{h}{2} \left( \vec{V}_{\!q}(\vec{q}_{n+1}) + 2 \mu_n \, \vec{q}_{n+1} \right) \\
    0 &= \vec{q}_{n+1} \cdot \vec{p}_{n+1}
\f}

\f{align*}{
    \vec{q}_{n+1} &= \vec{q}_n + h \, \vec{p}_n - \frac{h^2}{2} \vec{V}_{\!q}(\vec{q}_n) - h^2 \lambda_n \, \vec{q}_n \\
    &= \vec{a} + h^2 \lambda_n \, \vec{q}_n
\f}

\f{align*}{
    0 &= g(\vec{q}_{n+1}) = a^2 + h^4 \lambda_n^2 + 2h^2 \, \lambda_n \, \vec{a} \cdot \vec{q}_n - 1 \\
    \Leftrightarrow \quad
    0 &= \lambda_n^2 + 2\lambda_n \, \frac{\vec{a} \cdot \vec{q}_n}{h^2} + \frac{a^2 - 1}{h^4} \\
    \Leftrightarrow \quad
    \lambda_n &= -\frac{1}{h^2} \left( \vec{a} \cdot \vec{q}_n \pm \sqrt{ 1 + \left( \vec{a} \cdot \vec{q}_n \right)^2 - a^2} \right)
\f}

\f[
    \vec{q}_{n+1} = \vec{a} + \left( \vec{a} \cdot \vec{q}_n \pm \sqrt{ 1 + \left( \vec{a} \cdot \vec{q}_n \right)^2 - a^2} \right) \vec{q}_n
\f]

\f[
    \vec{p}_{n+1/2} = \vec{p}_n - \frac{h}{2} \vec{V}_{\!q}(\vec{q}_n) + \left( \vec{a} \cdot \vec{q}_n \pm \sqrt{ 1 + \left( \vec{a} \cdot \vec{q}_n \right)^2 - a^2} \right) \vec{q}_n
\f]

\f[
    \mu_n = \frac{\vec{q}_{n+1} \cdot \vec{p}_{n+1/2}}{h} - \frac{\vec{q}_{n+1} \cdot \vec{V}_{\!q}(\vec{q}_{n+1})}{2}
\f]

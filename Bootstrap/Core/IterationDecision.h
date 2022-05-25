/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef ITERATION_DECISION_H
#define ITERATION_DECISION_H

namespace Core {

    enum class IterationDecision {
        Continue,
        Break,
    };
}

using Core::IterationDecision;

#endif
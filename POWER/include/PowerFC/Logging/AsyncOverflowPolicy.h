#pragma once
namespace logging {

enum class AsyncOverflowPolicy
{
    Block,          // Block until message can be enqueued
    OverrunOldest,  // Discard the oldest message in the queue if full when trying to
                    // add new item.
    DiscardNew      // Discard new message if the queue is full when trying to add new item.
};
}
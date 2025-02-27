package main

import (
	"context"
	"fmt"
)

var buffer = make(chan int, 10)

type Producer struct {
	loops int
	name  string
	cacel context.CancelFunc
}

func (p *Producer) run() {
	for i := 0; i < p.loops; i++ {
		buffer <- i
		fmt.Printf("%s produced: %d\n", p.name, i)
	}
	close(buffer)
	p.cacel()
}

func InitProducer(cancel context.CancelFunc, loops int, name string) *Producer {
	p := Producer{
		loops: loops,
		name:  name,
		cacel: cancel,
	}
	return &p
}

type Consumer struct {
	name string
	ctx  context.Context
}

func InitConsumer(ctx context.Context, name string) *Consumer {
	consmer := Consumer{
		name: name,
		ctx:  ctx,
	}
	return &consmer
}

func (c *Consumer) run() {
	for {
		select {
		case i, ok := <-buffer:
			if !ok {
				return
			}
			fmt.Printf("%s consumed: %d\n", c.name, i)
		case <-c.ctx.Done():
			return
		}
	}
}

func main() {
	ctx, cancel := context.WithCancel(context.Background())

	p := InitProducer(cancel, 100, "Producer-1")
	c1 := InitConsumer(ctx, "Consumer-1")
	c2 := InitConsumer(ctx, "Consumer-2")

	go p.run()
	go c1.run()
	go c2.run()

	<-ctx.Done()
}

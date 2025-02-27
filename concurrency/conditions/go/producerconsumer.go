package main

import (
	"fmt"
	"sync"
	"time"
)

var mutex sync.Mutex = sync.Mutex{}

var EMPTY *sync.Cond = sync.NewCond(&mutex)
var FILL *sync.Cond = sync.NewCond(&mutex)

var MAX_SIZE int = 10

type List struct {
	buffer  []int
	fillIdx int
	useIdx  int
	count   int
}

var list List = List{
	buffer:  make([]int, MAX_SIZE),
	fillIdx: 0,
	useIdx:  0,
	count:   0,
}

func (list *List) put(i int) {
	list.buffer[list.fillIdx] = i
	list.fillIdx = (list.fillIdx + 1) % MAX_SIZE
	list.count++
}

func (list *List) get() int {
	tmp := list.buffer[list.useIdx]
	list.useIdx = (list.useIdx + 1) % MAX_SIZE
	list.count--
	return tmp
}

func (list *List) len() int {
	return list.count
}

type Producer struct {
	loops int
	name  string
}

func (p *Producer) run() {
	for i := 0; i < p.loops; i++ {
		mutex.Lock()

		for list.len() == MAX_SIZE {
			EMPTY.Wait()
		}
		list.put(i)
		fmt.Printf("produce: %d\n", i)
		FILL.Broadcast()
		mutex.Unlock()
	}
}

func InitProducer(loops int, name string) *Producer {
	p := Producer{
		loops: loops,
		name:  name,
	}
	return &p
}

type Consumer struct {
	name string
}

func InitConsumer(name string) *Consumer {
	consmer := Consumer{
		name: name,
	}
	return &consmer
}

func (c *Consumer) run() {
	for {
		mutex.Lock()
		for list.len() == 0 {
			FILL.Wait()
		}
		tmp := list.get()
		EMPTY.Signal()
		mutex.Unlock()
		fmt.Printf("%s consumes: %d\n", c.name, tmp)
	}
}

func main() {
	p := InitProducer(100, "Producer-1")
	c1 := InitConsumer("Consumer-1")
	c2 := InitConsumer("Consumer-2")

	go p.run()
	go c1.run()
	go c2.run()

	time.Sleep(5 * time.Second)
}

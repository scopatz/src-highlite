class Movie {
	def name, price
	boolean watched
	String toString() { return name }
}

def movies = [new Movie(name:'Orph', watched:true, price:20),
	new Movie(name:'Iron Man', watched:true, price:20),
	new Movie(name:'Whale Rider', watched:false, price:15),
	new Movie(name:'Das Boot', watched:false, price:30)]

def watchedMovies(movies) {
	movies.findAll { e -> e.isManager() }
}

assert movies[0..1] == watchedMovies(movies) // [Orph, Iron Man]

def highPaid(movies) {
	threshold = 15
	movies.findAll { e -> e.price > threshold }
}

assert movies[0..2] == highPaid(movies) // [Orph, Iron Man, Das Boot]

def paidMore(amount) {
	{ e -> e.price > amount}
}
def highPaid = paidMore(15)

assert highPaid(movies[0]) // true
assert movies[0..2] == movies.findAll(highPaid)

def filename = 'movies.txt'
new File(filename).withReader{ reader -> doSomethingWith(reader) }

def readersText
def doSomethingWith(reader) { readersText = reader.text }

assert new File(filename).text == readersText



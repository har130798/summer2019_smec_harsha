fetch('https://api.github.com/users/octocat')
    .then(res => {
        const jsonPromise = res.json()
        jsonPromise.then(data => {
            console.log(data)
        }).catch(err => {
            console.error(err)
        })
    }).catch(err => {
        console.error(err)
    })
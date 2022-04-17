import axios from 'axios'

const instance = axios.create({
    baseURL: process.env.VUE_APP_BACKEND_URL,
    headers: {
        'Authorization': {
            toString() {
                return `Bearer ${localStorage.getItem('token')}`
            }
        }
    }
});

export default instance